
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* routine(void* argv){

   
}

int main(int arg,char* argv[]){
    int count = arg -1;
 pthread_t th[count];
   int number[]={7,8,16,19};
   for (int i = 0; i < count; i++){
       FILE *fp = fopen(argv[i+1],"wb");
       if (fp<0)
       {
           perror("File is empty!");
           exit(-1);
       }
       fwrite(&number,sizeof(int),4,fp);
   }
   
    return EXIT_SUCCESS;
}
