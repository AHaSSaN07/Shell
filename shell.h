#ifndef SHELL_H_
#define SHELL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

/*********************************************/
/************** Golobal Variables ************/
/*********************************************/

char cmd[10][10][257];
char file_path[257];
int number_of_cmds, token_length;
int last_char_is_special;

int taking_file;
char c;
int flag_in , flag_out , flag_bg , flag_pipe;
char quotes;
int fd[2];
int fd2[2];
int file_id;
pid_t pid_2,pid_3,pid_4;
int i,j;
char *pointers[10][10];
int number_of_cmds_tokens[10];


extern char (*p_cmd)[10][257];    
extern char *p_file_path;

/*********************************************/
/************* Function Prototypes ***********/
/*********************************************/

void child_process(void);
void exe_proces(void);
int take_input(void);
void piping(void);

    
#endif 