#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "myshell.h"
#include <wait.h>
void execute(int processes) 
{
    int i, j, fd, pid;

    for(i = 0; i < processes; i++) {

        for(j = 0; process[i].commands[j] != NULL; j++) {

            if(strcmp(process[i].commands[j], ">") == 0) {
                process[i].commands[j] = '\0';
                fd = open(process[i].commands[++j], O_WRONLY| O_CREAT| O_TRUNC, S_IRUSR| S_IWUSR| S_IRGRP| S_IWGRP| S_IROTH| S_IWOTH);
                dup2(fd, 1);    
                close(fd);
  



                break;
            
            } else if(strcmp(process[i].commands[j], ">>") == 0) {
                process[i].commands[j] = '\0';
                fd = open(process[i].commands[++j], O_WRONLY| O_CREAT| O_APPEND, S_IRUSR| S_IWUSR| S_IRGRP| S_IWGRP| S_IROTH| S_IWOTH);
                dup2(fd, 1);
                close(fd);




                break;

            } else if(strcmp(process[i].commands[j], "<") == 0) {
                process[i].commands[j] = '\0';
                fd = open(process[i].commands[++j], O_RDONLY);
                dup2(fd, 0);
                close(fd);




                break;

            }else if(strcmp(process[i].commands[j], "2>") == 0) {
                process[i].commands[j] = '\0';
                fd = open(process[i].commands[++j], O_WRONLY| O_CREAT| O_TRUNC, S_IRUSR| S_IWUSR| S_IRGRP| S_IWGRP| S_IROTH| S_IWOTH);
                dup2(fd, 2);
                close(fd);




                break;
            }
        }

        if(processes == 1) { printf("%s %s\n", process[i].commands[0], process[i].commands[1]);
            if(!select_cmd()) { exit(0);}
            pid = fork();
            if(pid < 0) { perror("myshell: fork error"); }
            else if(pid == 0) { execlp(process[i].commands[0], process[i].commands); }
            else { wait(NULL); }
        
        } else { 
            if(!select_cmd()) { exit(0);}
            if(i == 0) {
                close(pip[0]);
                dup2(pip[1], 1);
                close(pip[1]);
            } else if (i > 0 && i < (processes - 1)) {
                close(pip[i]);
                dup2(pip[i - 1], 0);
                close(pip[i - 1]);
                close(pip[i + 1]);
                dup2(pip[i + 2], 1);
                close(pip[i + 2]);
            } else {
                close(pip[i + 1]);
                dup2(pip[i], 0);
                close(pip[i]);
            }
            
            pid = fork();
            if(pid < 0) { perror("myshell: fork error"); }
            else if(pid == 0) { execvp(process[i].commands[0], process[i].commands); }
            else { wait(NULL); }
        }
    }
        
}

       
            
 void do_pipe(int pipesize)
{   
    int i;
  

    for(i = 0; i < pipesize ; i += 2) {
        pipe(pip + i);
    }
}
                  
            
                
