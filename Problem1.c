
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>



pthread_mutex_t alpha;

void* symbols(void* arg){
     char name[10];
     pthread_mutex_lock(&alpha);
    for (int i = 0; i < 10; i++)
    {
       char cch = 'a' + rand()%26;
       name[i] += cch;
    }
    
    pthread_mutex_unlock(&alpha);
    
    printf("%s\n",name);

}

int main(int arg,char* argv[]){
    int count = atoi(argv[1]);
 pthread_t th[count];
 pthread_mutex_init(&alpha, NULL);
   for (int i = 0; i < count; i++){
        if(pthread_create(&th[i], NULL, symbols, NULL) != 0){
            perror("create thread:");
            return EXIT_FAILURE;
        }
    }

     for (int i = 0; i < count; i++){
        if(pthread_join(th[i], NULL) != 0){
            perror("join thread:");
            return EXIT_FAILURE;
        }
    }
    pthread_mutex_destroy(&alpha);
    return EXIT_SUCCESS;
}
