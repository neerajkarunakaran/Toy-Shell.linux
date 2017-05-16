#include <syscall.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "myshell.h"  // myshell header
int main()
{


    int fd;  // file descriptor 
    char *line, **args;   //

    init_sh();   //initialise  myshell
    do {


       printf("Myshell:-%s:>>", get_work_directory());  //myshell prompt 
       line = read_inputline();    //commands read from user

       args = convert_cmd(line);   // convert user commands into arguments vector


        io_redirection(args);  // check the presents of io redirection symbol in args and redirect

       select_cmd(args);  //check for inbuilt command and execute    
       close(fd);  //closing file
       free(line);  //freeing line and args
       free(args);
    } while (1);  //loop to another input
}



