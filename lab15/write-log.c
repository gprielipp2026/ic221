#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>

//TODO: Compile and set up to run as set-bit for the user
int main(int argc, char * argv[]){

    char * USAGE = "%s log-info\n";
    FILE * f_log;

    //TODO: update to reflect your directory
    char * path = "/courses/ic221/6541/m265112/log.txt";


    // Check arguments
    if (argc < 2){
        fprintf(stderr, "ERROR: require message to log\n");
        fprintf(stderr, USAGE, argv[0]); 
        exit(1);
    }

    // Clear?
    if(strcmp(argv[1],"CLEAR") == 0){

        // TODO: Test if *Real* UID matches your own
        // (Hint: find your own UID with the 'id' shell command)
        // If they *don't* match, print an error message and exit
        int myuid = 495044478;
        int ruid = getuid();
        if(ruid != myuid)
        {
          fprintf(stderr, "Invalid RUID\n");
          exit(1);
        }

        // Okay, they match.
        // Truncate the file (open it for writing, then close it).
        if( (f_log = fopen(path, "w")) == NULL){
              perror("fopen");
              fprintf(stderr, "ERROR: Cannot open log-file at '%s'\n",path);
              exit(1);
        }
        fclose(f_log);
        return 0;
    }

    // Open for append, if a new message is to be added
    if( (f_log = fopen(path, "a")) == NULL){
        perror("fopen");
        fprintf(stderr, "ERROR: Cannot open log-file at '%s'\n",path);
        exit(1);
    }

    // Compute a timestamp
    time_t t;
    time(&t);
    char * s = ctime(&t);
    s[strlen(s)-1] = '\0';

    // Write to the log
    fprintf(f_log, "[%s] (%d) %s\n", s, getuid(), argv[1]);

    // Close the log file
    fclose(f_log);

    return 0;
}
