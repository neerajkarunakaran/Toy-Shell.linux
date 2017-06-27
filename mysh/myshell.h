void init_sh (void);		/*initialise the shell */
char *read_inputline (void);	/* read input lines */
char *line;			/* place input lines */
char *get_work_directory (void);	/*get current work directory */
int select_cmd (void);		/* chech for inbuilt commands */
struct processes
{
  char *commands[15];
} process[10];
int process_creator (char *line);	/* convert input line into processes and its commands */
int *pip;			/* pipe place holder */
void do_pipe (int pipesize);	/* do pipes required for processes */
void execute (int processes);	/* execute commands */
void cd_fun (void);		/* change the current working directory */
void exit_fun (void);		/* exit from shell */
int nump;			/*  process number */
