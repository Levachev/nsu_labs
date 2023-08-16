#define _GNU_SOURCE 
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>


#define BUFFER_SIZE 13
#define PAGE_SIZE 4096

void rec_hw(int iter)
{
   if(iter==0)
   {
      return;
   }
   char s[] = "hello world";
   rec_hw(iter-1);
}

int fn(void *arg)
{
   rec_hw(10);

   return 0;
}

int main(int argc, char *argv[])
{
   const char *filepath = argv[1];
   int fd=open(filepath, O_RDWR);
   if(fd<0)
   {
      printf("could not open\n");
      return 0;
   }

   struct stat statbuf;
   int err=fstat(fd, &statbuf);
   if(err<0)
   {
      printf("could not open\n");
      return 0;
   }

   int size=statbuf.st_size-statbuf.st_size%PAGE_SIZE;

   printf("size - %d\n", size);

   void *ptr_stack=mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
   if(ptr_stack==MAP_FAILED)
   {
      printf("Mapping Failed\n");
      return 0;
   }

   int pid=clone(fn, ptr_stack+size, SIGCHLD, argv[1]);
   if(pid<0)
   {
      printf("ERROR\n");
      exit(EXIT_FAILURE);
   }

   wait(NULL);

   int ret_val2=munmap(ptr_stack, size);

   if(ret_val2!=0){
      printf("munmap erorr!\n");
      return 0;
   }
}