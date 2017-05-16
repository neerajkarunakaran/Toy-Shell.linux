#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "myshell.h"
#include <sys/types.h>
#include <wait.h>
 char *read_inputline(void)  //read input lines
{
    char *line = NULL;
    ssize_t bufsize = 0;
    getline(&line, &bufsize, stdin);  //get null terminated string
    return line;
}

char **convert_cmd(char *line)
{
    int bufsize =  TOK_BUF_SIZE;  // commands buffer
    int position = 0;

    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if(!tokens) {
        fprintf(stderr, "myshell: allocation error \n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, "\t\a\r' '\n");  //dividing the input string to commands
    while(token != NULL) {
        tokens[position] = token;
        position++;

        if(position >= bufsize){  //checking the buf size limit 

            bufsize += TOK_BUF_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));  //allocating additional space
            if(!tokens) {
                fprintf(stderr, "myshell: allocation error \n");
                exit(EXIT_FAILURE);
            }
        }
    
        token = strtok(NULL, "\t\r' '\n\a");
    }
    tokens[position] = '\0';
    argc = position;  //arguments count

    return tokens;
}


int execute_cmd(char **args) // execute the commands
{
    pid_t pid, wpid;
    int status;

    pid = fork();  //new process
    if(pid == 0) {
        if(execvp(args[0], args) == -1) { //exec command
            perror("myshell");
        }
        exit(EXIT_FAILURE);
    }
    else if(pid < 0) {
        perror("myshell");
    }
    else {
        wait(&status);  //suspend parent process

    }


}







    








     


