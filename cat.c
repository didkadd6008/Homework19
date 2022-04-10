#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char* argv[]){
    char buff[BUFSIZ];
    size_t bytes;

    if (argc <= 1)
        {
          
            while ((bytes=read(STDIN_FILENO,buff,BUFSIZ)) > 0)
            {
                write(STDOUT_FILENO,buff,bytes);
            }
            
        }else{
          for (int i = 1; i < argc; i++)
    {
        
        
        
            
            
            int fp = open(argv[i],O_RDONLY);
            if (fp == -1)
           {
               perror("error");
               return 1;
           }
            while ((bytes=read(fp,buff,BUFSIZ)) > 0)
            {
                write(STDOUT_FILENO,buff,bytes);
            }
           write(STDOUT_FILENO,"\n",i);
             
            close(fp);
    }
        }
    
        
    
    return 0;
}