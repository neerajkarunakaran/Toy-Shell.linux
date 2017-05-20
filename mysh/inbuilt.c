
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "myshell.h"
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <ctype.h>
char * get_work_directory(void)  //get current working directory
{
    char *current_directory;
    char buf[1024];
    current_directory = getcwd(buf, 1024);
    return current_directory;
}

void init_sh(void)  //initialise the myshell 
{
    chdir("/home");
}

void cd_fun(void) //change working directory`
{   


    if(process[0].commands[1] == NULL) {
        fprintf(stderr, "usage: cd \n");
    }
    else {
        chdir(process[0].commands[1]);
    }

}












void exit_fun(void)  //exit command
{
    _exit(0);
}

int select_cmd(void)
{   
    


    if(strcmp(process[0].commands[0], "cd") == 0) {
        cd_fun();
        return 0;
    }else if(strcmp(process[0].commands[0], "exit") == 0) {
        exit_fun();
        return 0;
    }
    return 1;
    
}


char *read_inputline(void)  //read input lines
{
   char *line = NULL;
   ssize_t bufsize = 0;
     getline(&line, &bufsize, stdin);  //get null terminated string
    return line;
}






  



   



  















   






















        


















        














    

    

        
        
    
        
        
      
        
    
























