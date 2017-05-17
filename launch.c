#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "myshell.h"
pipein = 0;
pos = 0;





void cmd_launcher(char **args)
{  
    int symbal = 0;
    int j = 0;
    int buf = TOK_BUF_SIZE;
    cmd = malloc(buf * sizeof(char *));
    if(! cmd) 
        { perror("allocation error"); }
    while(args[pos] != NULL) {
        if(strcmp(args[pos], ">") == 0) {
            symbal = 1;
            break;
        } else if(strcmp(args[pos], ">>") == 0) {
            symbal = 2;
            break;
        } else if(strcmp(args[pos], "<") == 0) {
            symbal = 3;
            break;
        } else if(strcmp(args[pos], "2>") == 0) {
            symbal = 4;
            break;
        } else if(strcmp(args[pos], "|") == 0) {
            symbal = 5;
            break;
        } else {
            cmd[j++] = args[pos];
            ++pos;
            continue;           
        }  
    }    
    cmd[j] = '\0'; 
 /*   i = 0;  
while(cmd[i] != NULL) { printf("%s\n", cmd[i++]);}  */
 printf("%d\n", symbal);   
    switch(symbal) {


        case 1: if(( fd = open(args[++pos], O_WRONLY| O_CREAT| O_TRUNC, S_IRUSR| S_IWUSR| S_IRGRP| S_IWGRP| S_IROTH| S_IWOTH)) < 0) {
                    perror("open file error");
                }
     
                close(1);
                if(dup(fd) == -1) { perror("dup die"); }

                if(strcmp(args[++pos], "|") == 0) {
                   
                    pipein = 1;
                    if(pipe(pip) < 0) {
                        perror("pipe error");
                    }
                    if(dup2(pip[1], 1) == -1) { perror("dup die"); }
                    ++pos;
                }
                symbal = 0;
                select_cmd(cmd);
                printf("%d\n", pos);
                close(fd);
                break;

        case 2: if((fd = open(args[++pos], O_WRONLY| O_CREAT| O_APPEND, S_IRUSR| S_IWUSR| S_IRGRP| S_IWGRP| S_IROTH| S_IWOTH)) < 0) {
                    perror("open file error");
                }

                if(dup2(fd, 1) == -1) { perror("dup die");}
                if(strcmp(args[++pos], "|") == 0) {
                    pipein = 1;
                    if(pipe(pip) < 0) {
                        perror("pipe error");
                    }
                    if(dup2(pip[1], 1) == -1) { perror("dup die");}
                }
                symbal = 0;
                select_cmd(cmd);
                close(fd);
                break;
        case 3: if((fd = open(args[++pos], O_RDONLY)) < 0) {
                    perror("open file error");
                }
                if(dup2(fd, 0) == -1) { perror("dup die"); }
                if(strcmp(args[++pos], "|") == 0) {
                    pipein = 1;
                    if(pipe(pip) < 0) {
                        perror("pipe error");
                    }
                    if(dup2(pip[1], 1) == -1) { perror(" dup die"); }
                }
                symbal = 0;
                close(fd);
                select_cmd(cmd);
                break;
        case 4: if((fd = open(args[++pos], O_WRONLY| O_CREAT| O_APPEND, S_IRUSR| S_IWUSR| S_IRGRP| S_IWGRP| S_IROTH| S_IWOTH)) < 0) {
                    perror("open file error");
                }
                if(dup2(fd, 2) == -1) { perror("dup die"); }
                if(strcmp(args[++pos], "|") == 0) {
                    pipein = 1;
                    if(pipe(pip) < 0) {
                        perror("pipe error");
                    }
                    if(dup2(pip[1], 1) == -1) { perror("dup die"); }
                }
                symbal = 0;
                close(fd);
                select_cmd(cmd);
                break;
        case 5: pipein = 1;
                if(pipe(pip) < 0) {
                    perror("pipe error");
                }
                if(dup2(pip[1], 1) == -1) { perror("dup die"); }
                symbal = 0;
                select_cmd(cmd);
                break;
        default: select_cmd(cmd);
                break;
    }
}
        
                
          
             
                
         
        

        
        
        

    

   
        
   



    
