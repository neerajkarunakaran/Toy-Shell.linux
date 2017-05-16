char *get_work_directory();
void init_sh(void);
#define BUFSIZE  100
#define TOK_BUF_SIZE  100
char *read_inputline(void);
char **convert_cmd(char *line);
#include <unistd.h>
int execute_cmd(char **args);
char *get_work_directory(void);
void select_cmd(char **args);
int io_redirection(char **args);
int fd;
int argc;
pid_t pid;
