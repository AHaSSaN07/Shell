
/*                        PROGRAM shell.c                               */
/*    This program runs a simple triminal with the basic tasks.         */
/* This code is written by and only by the hands of the legends :-      */
/* 1- Hossam El-Bahrawy     aka (Bazkleer)                              */
/* 2- Ahmed Habeila         aka (Smarta)                                */
/* 3- Ahmed Hassan          aka (Bubbly)                                */
/* 4- Mohamed Kassim        aka (Nagafa)                                */
/* -------------------------------------------------------------------  */

#include "shell.h"


char *p_file_path = file_path;



int main()
{
    pid_t pid_1;
    
    while(1)
    {

        printf("sish:> ");
        if(!take_input())
            {
                return 0;
            }        
        //forking a child for every command
        for (i = 0; i < number_of_cmds; i++) {
    		for (j = 0; j < number_of_cmds_tokens[i]; j++) {
    			pointers[i][j] = *(*(cmd + i) + j);
    		}
    		pointers[i][j] = NULL;
    	}

        pid_1 = fork();
    
        if( pid_1 < 0 ) //if child isn't created
        {
            printf("ERROR: Failed to fork  process #1!\n");
            exit(1);
        }
        
        else if( pid_1 ==0 ) // child is Runnning 
        {
            child_process();
        }
        
        
        if(!flag_bg)
        usleep(100000);

        
    }
    return 0;            
}