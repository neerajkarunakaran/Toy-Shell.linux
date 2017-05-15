#include <syscall.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "myshell.h"
int main()
{

    char *line, **args;
    int status;
    init_sh();
    do {


       printf("Myshell:-%s:>>", get_work_directory());
       line = read_inputline();
       args = convert_cmd(line);
       execute_cmd(args);

       free(line);
       free(args);
    } while (1);
}



