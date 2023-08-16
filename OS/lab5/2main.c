#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int my_global=9;

int main(int argc,char *argv[]) {
  pid_t first_pid = getpid();

  pid_t pid = fork();

  if(pid == 0) 
  {
    exit(5);
  }
  else if(pid > 0) 
  {

    sleep(30);

    /*int status;
    if (wait(&status) >= 0)
    {
        if (WIFEXITED(status))
        {
            printf("Child process exited with %d status\n", WEXITSTATUS(status));
        }
        printf("parent status - %d\n", status);
    }*/

  }
  else 
  {
    printf("erorr\n");
  }

  return 0;
}