#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

int value = 5;
int main(int argc, char *argv[]) {
    int pid;
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    int timeI=current_time.tv_usec;
    pid = fork();
    char *argv2[argc-1];
    for (int i = 1; i < argc; i++){
        argv2[i-1]=argv[i];
    }
    
    if (pid == 0) { /* child process */
        execvp(argv2[0],argv2);
        
        printf("%s\n",argv[0]);
        
        
    }
    else if (pid > 0) { /* parent process */
        wait(NULL);
        gettimeofday(&current_time, NULL);
        int timeF=current_time.tv_usec;
        printf("Elapsed time: %d",timeF-timeI);
        return 0;
    }
}