#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

void* routine(void* argv){
printf("%s\n",(char*)argv);
}

int main(int arg,char* argv[]){
int processes = atoi(argv[1]);
int threads = atoi(argv[2]);

for (int i = 0; i < processes; i++)
{
    pid_t pid = fork();
    if (0 == pid)
    {
        pthread_t th[threads];
         for (int i = 0; i < threads; i++){
        if(pthread_create(&th[i], NULL, routine, argv[3]) != 0){
            perror("create thread:");
            return EXIT_FAILURE;
        }
    }

     for (int i = 0; i < threads; i++){
        if(pthread_join(th[i], NULL) != 0){
            perror("join thread:");
            return EXIT_FAILURE;
        }
    }
        exit(EXIT_SUCCESS);
    }
    
    
}

for (int i = 0; i < processes; i++)
{
    wait(NULL);
}

return(EXIT_SUCCESS);
}
