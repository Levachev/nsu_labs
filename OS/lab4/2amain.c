#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>


int main(int argc,char *argv[]) {
  
  pid_t pid = getpid();
  printf("pid: %d\n", pid);
  printf("Hello world\n");

  sleep(1);

  char* arr[] = {argv[0], NULL};

  execv(argv[0],argv);

  return 0;
}