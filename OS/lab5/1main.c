#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int my_global=9;

int main(int argc,char *argv[]) {
  pid_t first_pid = getpid();
  printf("first_pid: %d\n", first_pid);

  sleep(10);

  int my_local=7;

  printf("my_local adress - %p\n", &my_local);
  printf("my_local value - %d\n", my_local);

  printf("my_global adress - %p\n", &my_global);
  printf("my_global value - %d\n", my_global);


  pid_t pid = fork();

  if(pid == 0) 
  {
    sleep(30);
    printf("ppid - %d , pid - %d\n", getppid(), getpid());

    printf("my_local adress - %p\n", &my_local);
    printf("my_local value - %d\n", my_local);

    printf("my_global adress - %p\n", &my_global);
    printf("my_global value - %d\n", my_global);

    my_local=11;
    my_global=19;

    printf("my_local value - %d\n", my_local);
    printf("my_global value - %d\n", my_global);

    exit(5);

  }
  else if(pid > 0) 
  {
    sleep(30);
    printf("int parent\n");

    printf("my_local value - %d\n", my_local);
    printf("my_global value - %d\n", my_global);

    sleep(30);

    int status;
    if (wait(&status) >= 0)
    {
        if (WIFEXITED(status))
        {
            printf("Child process exited with %d status\n", WEXITSTATUS(status));
        }
        printf("parent status - %d\n", status);
    }

  }
  else 
  {
    printf("erorr\n");
  }

  return 0;
}