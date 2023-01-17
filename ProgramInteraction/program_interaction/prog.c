#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>
void pwncollege(){
   return;
}
int main(){
   /*int fd1[2];
   pipe(fd1);
   int fd2[2];
   pipe(fd2);
   if(fork()==0){
      close(fd1[0]);
      close(fd2[0]);
      close(fd2[1]);
      dup2(fd1[1],1);
      sleep(1);
      execv("cat",NULL);
   }*/
   if(fork() == 0 ){
     /*
      close(fd1[1]);
      close(fd2[0]);
      dup2(fd1[0],0);
      dup2(fd1[1],1);
      */
      //sleep(10);
      execv("/challenge/embryoio_level139", NULL);
   }/*
   if(fork()==0){
      close(fd1[0]);
      close(fd1[1]);
      close(fd2[1]);
      dup2(fd2[0],0);
      execv("cat",NULL);
   }
   */
   else{
      pwncollege();
      while(wait(NULL) > 0);
}
}