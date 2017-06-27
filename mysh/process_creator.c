#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include "myshell.h"
/* convert line input into processes and its commands */
int
process_creator (char *line)
{

  char *cmd, *token, *rest;
  int pposition, cposition;	/* process and commands position */
  pposition = cposition = 0;

  token = strtok (line, "|");	/* split the line by  into proper number of processes */
  while (token != NULL)
    {
      rest = token;
      while ((cmd = strtok_r (rest, "' '\t\r\a\n", &rest)) != NULL)
	{			/* split process string into proper arguments */
	  process[pposition].commands[cposition] = cmd;
	  ++cposition;
	  if (cposition > 15)
	    {
	      perror ("arguments limit exceed");
	    }
	}
      process[pposition].commands[cposition] = '\0';
      cposition = 0;
      ++pposition;
      if (pposition > 10)
	{
	  perror ("processes limit exceeds");
	}

      token = strtok (NULL, "|");
    }
  return pposition;		/* return number of processes */
}
