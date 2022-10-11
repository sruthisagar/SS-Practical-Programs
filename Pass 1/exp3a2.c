#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
 pid_t pid;
 printf("Parent process with pid %d\n",(int)getpid());
 pid=fork();
 if(pid<0){
 fprintf(stderr,"Fork failed");
 }
 else if(pid==0){
 printf("Child process with pid %d\n",(int)getpid());
 exit(0);
 sleep(5);
 }
 else{
 wait();
 printf("Child process exited without executing sleep() function\n");
 }
}
