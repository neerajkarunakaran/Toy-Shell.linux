
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "myshell.h"

char * get_work_directory()
{
    char *current_directory;
    char buf[100];
    current_directory = getcwd(buf, 100);
    return current_directory;
}

void init_sh(void)
{
    chdir("/home");
}


























