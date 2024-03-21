#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_ARGS 128
#define MAX_CMDS 128

int main(int argc, char * argv[]){

	// Pipes to use
	int cur_pipe[2];
	int last_pipe[2];
	
	int i, status;
	pid_t cpid;		// Used during the fork
	char* commands[MAX_CMDS];
	char* pipeline[MAX_CMDS][MAX_ARGS];
    char* token;
	char* command;

	// Read a line from supplied arguments in argv
	if (argc < 2) {
		printf("Usage: ./pipe <pipeline_string>");
		exit(1);
	}
	char * line = argv[1];

	// Parse the line into commands separated by '|'
	int command_count = 0;
    while(command_count < MAX_ARGS) {
		if (command_count == 0) token = strtok(line, "|");
		else token = strtok(NULL,"|");
		if (token == NULL) 
			break;
		commands[command_count] = token;
		command_count++;
	}
	commands[command_count] = NULL;

	// Parse the commands into args separated by ' '
	for(i=0; i < command_count; i++) {
		command = commands[i];
		int arg_count = 0;
		while(arg_count < MAX_ARGS) {
			if (arg_count == 0) token = strtok(command," ");
			else token = strtok(NULL," ");
			if (token == NULL)
				break;
			pipeline[i][arg_count] = token;
			arg_count++;
		}
		pipeline[i][arg_count] = NULL;
	}
	pipeline[i][0] = NULL;

// *****************************
  
	for(i=0; pipeline[i][0] != NULL; i++){
  
		// Create the current pipe *unless* there is no next command
		//   (i.e., unless this is the last one)
		if(pipeline[i+1][0] != NULL){
			
			// TODO: create (open) the current pipe

		}

		cpid = fork();
		
		if ( cpid == 0) {		/* CHILD */

			// If not at the end, handle the 'right' side of this process
			if( pipeline[i+1][0] != NULL ) {
				
				// TODO: close the read end of the right pipe

				// TODO: close the old stdout

				// TODO: duplicate the write end of the right pipe to stdout		

			}

			// If not at the start, handle the 'left' side of this process
			if( i > 0 ) {
				
				// TODO: Close the write end of the left pipe

				// TODO: Close the old stdin

				// TODO: Duplicate the read end of the left pipe to stdin

			}

			// TODO: Execute this stage in pipeline with execvp()



		}
		else if ( cpid > 0) {		/*PARENT*/
		
			// TODO: Shift pipes -- set current to last
			//   (move both the 'read' and 'write' ends!)


			
			// TODO: close the write end of last_pipe

		}
		else {	/*ERROR*/
			perror("fork");
			_exit(1);	
		} 
		
	}  // end 'for' loop

// *****************************

	//wait for all children, then exit
	while( wait(&status) > 0);
	return 0;
}
