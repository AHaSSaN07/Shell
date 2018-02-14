#include "shell.h"

void exe_process()
{

	if (flag_pipe )
	{
		piping();
	}
	else
	{
		if (flag_in)
		{
			close(1);
			file_id = open(file_path, O_WRONLY | O_CREAT, 0644);

		}
		
		else if (flag_out)
		{
			close(0);
			file_id = open(file_path, O_RDONLY, 0400);
		}

		if(execvp(pointers[0][0], pointers[0]))
		{
			printf("ERROR: exec failed %s not found\n", pointers[0][0]);
		}
	}
}


void piping()
{
	for(i=0;i<number_of_cmds;i++)
	{
		pipe(fd);
		pid_1=fork();
		if(pid_2==0)
		{  
	    	dup2(fd[1],1);
	    	close(fd[0]);
	    	close(fd[1]);
	    	flag_pipe=0;
			exe_process();
	    	exit(1);
			
		}
	}
	/*pipe(fd);
	pipe(fd2);
	pid_2=fork();
		
	if(pid_2==0){ //is in first child
	    dup2(fd[1],1);
	    close(fd[0]);
	    close(fd[1]);
	    flag_pipe=0;
	    exe_process();
	    exit(1);
	}
	else   //is in parent
	{
		pid_3=fork();
		
	    if(pid_3==0) //is in another/2nd child{
	     {  dup2(fd[0], 0);
	        close(fd[1]);
	        close(fd[0]);
	        
	        if (number_of_cmds>2)
	        {
	        dup2(fd2[1],1);
	    	close(fd2[0]);
	    	close(fd2[1]);}
	        execvp(pointers[1][0],pointers[1]);
	        exit(1);
	     }
	     
	     wait(NULL);
	     
	     if(number_of_cmds > 2)
	     {
		     pid_4=fork();
		     if(pid_4==0)
		     {
		     	
		     	 dup2(fd2[0],0);
		    	close(fd2[0]);
		    	close(fd2[1]);
		        execvp(pointers[2][0],pointers[2]);
		    	
		        exit(1);
		     }
	     }
	   
	 }  */ 

	return;
}



void child_process()
{
	
	exe_process();
	exit(0);
}


int take_input() {
	number_of_cmds = 0, token_length = 0;
	last_char_is_special = 0;
	flag_in = 0, flag_out = 0, flag_bg = 0, flag_pipe = 0;
	quotes = 0;
	taking_file = 0;
	p_file_path = file_path;

	memset(cmd, 0, sizeof(cmd)); // 25700 = 257 * 10 * 10
	memset(pointers, 0, sizeof(pointers));
	memset(number_of_cmds_tokens, 0, sizeof(number_of_cmds_tokens));
	memset(file_path, 0, sizeof(file_path));


	while (1) {
		char previous_c = c;
		c = getchar();
		switch (c) {
		case '"':			//toggle opening/closing quotes
			if (quotes) {
				quotes = 0;
				last_char_is_special = 1;
				number_of_cmds_tokens[number_of_cmds]++;
			}
			else {
				quotes = 1;
				if (!last_char_is_special) number_of_cmds_tokens[number_of_cmds]++;
				token_length = 0;
				last_char_is_special = 0;
			}
			break;
		case '<':
			if (!quotes) {
				flag_out = 1;
				token_length = 0;
				taking_file = 1;
				if (!last_char_is_special) number_of_cmds_tokens[number_of_cmds]++;
				last_char_is_special = 1;
			}
			else {
				if (!taking_file) {
					*(*(*(cmd + number_of_cmds) + number_of_cmds_tokens[number_of_cmds]) + token_length) = c;
					token_length++;
					last_char_is_special = 0;
					break;
				}
				else {
					last_char_is_special = 0; *p_file_path = c;
					p_file_path++;
				}
			}
			break;
		case '>':
			if (!quotes) {
				flag_in = 1;
				token_length = 0;
				taking_file = 1;
				if (!last_char_is_special) number_of_cmds_tokens[number_of_cmds]++;
				last_char_is_special = 1;
			}
			else {
				if (!taking_file) {
					*(*(*(cmd + number_of_cmds) + number_of_cmds_tokens[number_of_cmds]) + token_length) = c;
					token_length++;
					last_char_is_special = 0;
					break;
				}
				else {
					last_char_is_special = 0; *p_file_path = c;
					p_file_path++;
				}
			}
			break;
		case '|':
			if (!quotes) {
				if (!last_char_is_special && !taking_file) number_of_cmds_tokens[number_of_cmds]++;
				number_of_cmds++;
				last_char_is_special = 1;
				token_length = 0;
				flag_pipe = 1;
				taking_file = 0;
			}
			else {
				if (!taking_file) {
					*(*(*(cmd + number_of_cmds) + number_of_cmds_tokens[number_of_cmds]) + token_length) = c;
					token_length++;
					last_char_is_special = 0;
					break;
				}
				else {
					last_char_is_special = 0; *p_file_path = c;
					p_file_path++;
				}
			}
			break;
		case '&':
			if (!quotes) {
				flag_bg = 1;
				last_char_is_special = 1;
			}
			else {
				if (!taking_file) {
					*(*(*(cmd + number_of_cmds) + number_of_cmds_tokens[number_of_cmds]) + token_length) = c;
					token_length++;
					last_char_is_special = 0;
					break;
				}
				else {
					last_char_is_special = 0; *p_file_path = c;
					p_file_path++;
				}
			}
			break;
		case ' ':
			if (!quotes && !last_char_is_special) {
				token_length = 0;
				if (!taking_file && !last_char_is_special) number_of_cmds_tokens[number_of_cmds]++;
				last_char_is_special = 1;
				taking_file = 0;
			}
			else if (quotes) {
				*(*(*(cmd + number_of_cmds) + number_of_cmds_tokens[number_of_cmds]) + token_length) = c;
				token_length++;
				last_char_is_special = 0;
			}
			break;
		case '\t': //same as whitespaces
			if (!quotes && !last_char_is_special) {
				token_length = 0;
				if (!taking_file && !last_char_is_special) number_of_cmds_tokens[number_of_cmds]++;
				last_char_is_special = 1;
				taking_file = 0;
			}
			else if (quotes) {
				*(*(*(cmd + number_of_cmds) + number_of_cmds_tokens[number_of_cmds]) + token_length) = c;
				token_length++;
				last_char_is_special = 0;
			}
			break;
		case '\n':
			if (!taking_file && !last_char_is_special) number_of_cmds_tokens[number_of_cmds]++;
			number_of_cmds++;
			if (flag_bg && previous_c != '&')
				return -1;
			if (strcmp(*(*(cmd)), "exit") == 0){
				printf("Okay, exiting... :(\n");
				return 0;
			}
			if (quotes)
				return -2;
			for (i = 0; i < number_of_cmds; i++) {
				for (j = 0; j < number_of_cmds_tokens[i]; j++) {
					pointers[i][j] = (*(*(cmd + i) + j));
				}
				pointers[i][j] = NULL;
			}
			return 1;
		case EOF: //same as \n
			if (!taking_file && !last_char_is_special) number_of_cmds_tokens[number_of_cmds]++;
			number_of_cmds++;
			if (flag_bg && previous_c != '&')
				return -1;
			if (strcmp(*(*(cmd)), "exit") == 0){
				printf("Okay, exiting... :(\n");
				return 0;
			}
			if (quotes)
				return -2;
			for (i = 0; i < number_of_cmds; i++) {
				for (j = 0; j < number_of_cmds_tokens[i]; j++) {
					pointers[i][j] = (*(*(cmd + i) + j));
				}
				pointers[i][j] = NULL;
			}
			return 1;		//kasim b3bs hena
		default:
			if (!taking_file) {
				*(*(*(cmd + number_of_cmds) + number_of_cmds_tokens[number_of_cmds]) + token_length) = c;
				token_length++;
				last_char_is_special = 0;
				break;
			}
			else {
				last_char_is_special = 0;
				*p_file_path = c;
				p_file_path++;
			}
		}
	}
}
