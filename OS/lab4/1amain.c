#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 100

void init_buffer(char* buffer)
{
  buffer[0]='h';
  buffer[1]='e';
  buffer[2]='l';
  buffer[3]='l';
  buffer[4]='o';
  buffer[5]=' ';
  buffer[6]='w';
  buffer[7]='o';
  buffer[8]='r';
  buffer[9]='l';
  buffer[10]='d';
  buffer[12]='!';
}

void print_buffer(char* buffer)
{
  for(int i=0;i<BUFFER_SIZE;i++){
    printf("%c", buffer[i]);
  }
  printf("\n");
}

void work_with_buffer()
{
  char* buffer1;
  buffer1=(char*)malloc(BUFFER_SIZE*sizeof(char));
  for(int i=11;i<BUFFER_SIZE;i++){
    buffer1[i]=33;
  }
  init_buffer(buffer1);
  print_buffer(buffer1);
  free(buffer1);
  print_buffer(buffer1);

  char* buffer2;
  buffer2=(char*)malloc(BUFFER_SIZE*sizeof(char));
  init_buffer(buffer2);
  print_buffer(buffer2);
  buffer2=&buffer2[BUFFER_SIZE/2];
  free(buffer2);
  print_buffer(buffer2);
}

int my_init_in_global=9;

int my_not_init_in_global;

const int my_const_in_global=7;

void my_func()
{
  int my_local_in_func;
  static int my_static_in_func;
  const int my_const_in_func=5;

  printf("my_local_in_func adress - %p\n", &my_local_in_func);
  printf("my_static_in_func adress - %p\n", &my_static_in_func);
  printf("my_const_in_func adress - %p\n", &my_const_in_func);
}

int* return_adress_of_local()
{
  int tmp=1;
  return &tmp;
}

void print_env()
{
  printf("MYENV : %s\n", getenv("MYENV"));
}

int main(int argc,char *argv[]) {
  /*work_with_buffer();

  printf("\n\n\n\n");

  printf("return_adress_of_local adress - %p\n", return_adress_of_local());   */                       //указаель на несущ обьект, способ сказать что не было проиниц

  /*pid_t pid = getpid();
  printf("pid: %d\n", pid);

  my_func();

  printf("my_init_in_global adress - %p\n", &my_init_in_global);
  printf("my_not_init_in_global adress - %p\n", &my_not_init_in_global);
  printf("my_const_in_global adress - %p\n", &my_const_in_global);*/
  printf("%p\n", return_adress_of_local());
  sleep(30000);

  /*print_env();
  setenv("MYENV", "newValue", 1);
  print_env();*/

  return 0;
}