#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int pid;
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    int timeI=current_time.tv_usec;
    char **arg_vector = NULL;
    arg_vector = (char **)malloc(sizeof(char **) *(argc-1));
    if (arg_vector == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    char path[50];
    strcpy(path,"/bin/");
    pid = fork();
    for (int i = 1; i < argc; i++){
        arg_vector[i-1]=argv[i];
    }
    arg_vector[argc]=NULL;
    
    if (pid == 0) { /* child process */
        strcat(path,arg_vector[0]);
        arg_vector[0]=path;
        execv(arg_vector[0],arg_vector);
        perror("execv");
    }
    else if (pid > 0) { /* parent process */
        wait(NULL);
        gettimeofday(&current_time, NULL);
        int timeF=current_time.tv_usec;
        printf("\nElapsed time: %d\n",timeF-timeI);
        return 0;
    }
}