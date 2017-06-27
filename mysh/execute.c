#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "myshell.h"
#include <wait.h>
#include <string.h>
void
execute (int processes)
{
  pid_t pid;
  for (nump = 0; nump < processes; nump++)
    {				/* loop with processes */
      pid = fork ();		/* creat new process */
      if (pid < 0)
	{
	  perror ("fork error");
	  exit (EXIT_FAILURE);
	}
      else if (pid == 0)
	{
	  int numc, fd;
	  for (numc = 0; process[nump].commands[numc] != NULL; numc++)
	    {			/* loop through process commands and check for i/o redirection */
	      if (strcmp (process[nump].commands[numc], ">") == 0)
		{		/*process argument cmp with output redirection  */
		  process[nump].commands[numc] = '\0';
		  fd =
		    open (process[nump].commands[++numc],
			  O_WRONLY | O_CREAT | O_TRUNC,
			  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH |
			  S_IWOTH);
		  dup2 (fd, 1);	/* duplicate the file fd with stdout */
		  close (fd);

		  break;

		}
	      else if (strcmp (process[nump].commands[numc], ">>") == 0)
		{		/* process argument cmp with  output apend resirection */
		  process[nump].commands[numc] = '\0';
		  fd =
		    open (process[nump].commands[++numc],
			  O_WRONLY | O_CREAT | O_APPEND,
			  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH |
			  S_IWOTH);
		  dup2 (fd, 1);
		  close (fd);
		  break;
		}
	      else if (strcmp (process[nump].commands[numc], "<") == 0)
		{		/* process argument cmp with input redirection */
		  process[nump].commands[numc] = '\0';
		  fd = open (process[nump].commands[++numc], O_RDONLY);
		  dup2 (fd, 0);
		  close (fd);
		  break;
		}
	      else if (strcmp (process[nump].commands[numc], "2>") == 0)
		{		/* process argument cmp with stderr redirection */
		  process[nump].commands[numc] = '\0';
		  fd =
		    open (process[nump].commands[++numc],
			  O_WRONLY | O_CREAT | O_TRUNC,
			  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH |
			  S_IWOTH);
		  dup2 (fd, 2);
		  close (fd);
		  break;
		}
	    }


	  if (processes == 1)
	    {			/* execute single process */


	      if (execvp (process[nump].commands[0], process[nump].commands)
		  == -1)
		{		/*call exec sys call to execute process */
		  perror ("exec failure");

		  exit (EXIT_FAILURE);
		}

	    }


	  else
	    {			/* check for multi processes */

	      if (nump == 0)
		{		/* set pipe for start process */
		  close (pip[nump]);
		  dup2 (pip[nump + 1], 1);

		}
	      else if (nump > 0 && nump < (processes - 1))
		{		/*set virtual file for intermediate processes */
		  close (pip[nump]);
		  dup2 (pip[nump - 1], 0);

		  close (pip[nump + 1]);
		  dup2 (pip[nump + 2], 1);

		}
	      else
		{		/* set pipe for last process */
		  close (pip[nump]);
		  dup2 (pip[nump - 1], 0);

		}

	      if (execvp (process[nump].commands[0], process[nump].commands)
		  == -1)
		{		/*exec process */
		  perror ("exec failure");
		  exit (EXIT_FAILURE);
		}

	    }
	}
      else
	{
	  wait (NULL);		/* wait for child to run */
	}
    }				/* loop thruogh processes */
}





void
do_pipe (int pipesize)		/* set number of virtual file required for all processes */
{
  int i;

  for (i = 0; i < pipesize; i += 2)
    {
      pipe (pip + i);
    }
}
