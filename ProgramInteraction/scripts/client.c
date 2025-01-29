#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>
void pwncollege(){}


int main(int argc, char** argv){
   int sockfd = socket(PF_INET, SOCK_STREAM, 0);
   struct sockaddr_in dest_addr;
   dest_addr.sin_family = AF_INET;    
   dest_addr.sin_port = htons(1281);
   inet_aton("127.0.0.1", &dest_addr.sin_addr);
   memset(&(dest_addr.sin_zero), '\0', sizeof dest_addr.sin_zero); 
   int rev = connect(sockfd, (struct sockaddr*)& dest_addr, sizeof dest_addr);
   char buff[128], buff1[128];
   int n,i;

   while(1){
    n = read(sockfd, buff, sizeof(buff));
    buff[n] = '\0';
    //printf("%d  %s\n",i,buff);
   char*rev =  strstr(buff, "pwn.college{");
   if(rev){
      printf("%s", buff);
   }
   char* ret = strstr(buff, "solution");
   if (ret){
      //char *e;
      //char exp[100];
      //memset(exp, '\0', sizeof(exp));
      //int index;
      //e = strchr(buff, ':');
      //index = (int)(e - buff);
      //strncpy(exp, buff + index+2, sizeof(exp));
      printf("%s", buff);
      read(0, buff1, sizeof(buff1));
      write(sockfd, buff1, strlen(buff1));
      memset(buff1, '\0', sizeof(buff1));
   }
   }
   
  /* 
   printf("bfuf\n");
   for (i=0;i<5;i++){
     n = read(sockfd, buff, sizeof(buff));
     printf("bfufug\n");
      printf("%d  %s", i,buff);
     printf("bfufug\n");
     n = read(0, buff1, sizeof(buff));
     printf("bfufug\n");
     write(sockfd, buff1, strlen(buff1));
     printf("bfufug\n");
   }
   
    print("=========================")
    lane1 = lane[lane.find(':')+2:-1]
    print(lane1)
    print("=========================")
    sol = eval(lane1)
    print(sol)
    print("=========================")
    p.sendline(str(sol))
    print(p.recvline())
   The redirection operator

n<>word
causes the file whose name is the expansion of word to be opened for both reading and writing on file descriptor n,
or on file descriptor 0 if n is not specified. If the file does not exist, it is created.
   */
   close(sockfd);
   exit(0);
}
