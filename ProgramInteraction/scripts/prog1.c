#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
void pwncollege(){
   return;
}
int main(){
   mkfifo("/ffo1", 0666);
   mkfifo("/ffo2", 0666);
int fd1 = open("ffo1",O_RDWR);
int fd2 = open("ffo2",O_RDWR);

    int pid = fork();
   if(pid == 0 ){ 
      dup2(fd1, 0);
      dup2(fd2,1);
      execv("/challenge/embryoio_level120", NULL);
   }
   else{
      pwncollege();
      waitpid(pid, NULL, 0);
      }
}