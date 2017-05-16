
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "myshell.h"
#include <string.h>
#include <fcntl.h>

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

void cd_fun( char **args) //change working directory`
{   
    char *pwd;
    int i = 0;
    if(args[1] == NULL) {
        fprintf(stderr, "usage: cd \n");
    }
    else if(strcmp(args[1], "..") == 0) {  //
        pwd = get_work_directory();
        while(pwd[i] != '\0') {
            ++i;
        }
        while(pwd[i] != '/') {
           --i;
        }
        pwd[i] = '\0';
        chdir(pwd);
     }

     else {
            chdir(args[1]);
     }
}

void exit_fun(char **args)  //exit command
{
    _exit(0);
}

void select_cmd(char **args) //check for inbuilt command
{   
    


    if(strcmp(args[0], "cd") == 0) {
        cd_fun(args);
    }else if(strcmp(args[0], "exit") == 0) {
        exit_fun(args);
    }else {
        execute_cmd(args);
    }
}


 int io_redirection(char **args)
{   

    if (argc < 3) {
        return 0;
      }
  
    else if(strcmp(args[argc - 2], ">") == 0) {   
        fd = open(args[argc - 1], O_WRONLY| O_CREAT, S_IRUSR| S_IWUSR| S_IRGRP| S_IWGRP| S_IROTH| S_IWOTH);
        args[argc - 2] = '\0';
   
        dup2(fd, 1);
        return fd;
  
    } else if(strcmp(args[argc - 2], "<") == 0 ) {
        fd = open(args[argc - 1], O_RDONLY, S_IRUSR| S_IWUSR| S_IRGRP| S_IWGRP| S_IROTH| S_IWOTH);
        args[argc - 2] = '\0';
        dup2(fd, 0);
        return fd;

    } else if(strcmp(args[argc - 2], ">>") == 0) {
        fd = open(args[argc - 1], O_WRONLY| O_CREAT| O_APPEND, S_IRUSR| S_IWUSR| S_IRGRP| S_IWGRP| S_IROTH| S_IWOTH);
        args[argc - 2] = '\0';
        dup2(fd, 1);
        return fd;
    } else {
        return 0;
    }
}





















        


















        














    

    

        
        
    
        
        
      
        
    
























