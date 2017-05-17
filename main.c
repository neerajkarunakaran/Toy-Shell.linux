#include <syscall.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "myshell.h"  // myshell header
int main()
{


    int fd;  // file descriptor 

 /*   int pip[2];
    int pipein = 0;
    int pos = 0; */
    init_sh();   //initialise  myshell
    do {


       printf("Myshell:-%s:>>", get_work_directory());  //myshell prompt 
       line = read_inputline();    //commands read from user

       args = convert_cmd(line);   // convert user commands into arguments vector


       cmd_launcher(args);

 //      select_cmd(args);  //check for inbuilt command and execute    
 //      close(fd);  //closing file
       free(line);  //freeing line and args
       free(args);
    } while (1);  //loop to another input
}



