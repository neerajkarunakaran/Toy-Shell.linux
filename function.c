#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "myshell.h"
 char *read_inputline(void)
{
    char *line = NULL;
    ssize_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

char **convert_cmd(char *line)
{
    int bufsize =  TOK_BUF_SIZE;
    int position = 0;

    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if(!tokens) {
        fprintf(stderr, "myshell: allocation error \n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, "\t\r\n\a");
    while(token != NULL) {
        tokens[position] = token;
        position++;

        if(position >= bufsize){
            bufsize += TOK_BUF_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if(!tokens) {
                fprintf(stderr, "myshell: allocation error \n");
                exit(EXIT_FAILURE);
            }
        }
    
        token = strtok(NULL, "\t\r\n\a");
    }
    tokens[position] = '\0';
    return tokens;
}


int execute_cmd(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if(pid == 0) {
        if(execvp(args[0], args) == -1) {
            perror("myshell");
        }
        exit(EXIT_FAILURE);
    }
    else if(pid < 0) {
        perror("myshell");
    }
    else {
        wait();
    }

    return 1;
}







    








     


