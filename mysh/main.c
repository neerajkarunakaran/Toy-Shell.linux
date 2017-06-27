#include <syscall.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "myshell.h"		// myshell header
int
main ()
{
  int fd, pipesize, processes;	// file descriptor 
  char hostname[20], *loginname;
  init_sh ();			//initialise  myshell
  while (1)
    {
      loginname = getlogin ();	/* get loginname */
      gethostname (hostname, 20);	/*get host name */
      printf ("%s@%s:-%s$", loginname, hostname, get_work_directory ());	//myshell prompt 
      line = read_inputline ();	/* read input line */
      processes = process_creator (line);	/* convert line into processes and its args */
      if (processes > 1)
	{			/* set pipe */
	  pipesize = (2 * processes) - 2;
	  pip = malloc (pipesize * sizeof (int));
	  do_pipe (pipesize);
	}
      if (select_cmd ())
	{			/* check for inbuilt commands */
	  execute (processes);
	}			/* execute commands */
      free (line);		//freeing line and args
    }				//loop to another input
}
