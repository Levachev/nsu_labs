#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <signal.h>

#define BUFFER_SIZE 4096
#define ITER 10000
#define PAGE_SIZE 4096

char **A;

void sig_handler(int signal){
    printf("SIGSEGV\n");
    exit (0);
}

void recur_alloc()
{
  char arr[4096]={'0'};
  printf("adresses - %p  --  %p\n", arr, &arr[4095]);
  sleep(10);
  recur_alloc();
}

void alloc_in_heap()
{
    A=(char**)malloc(ITER*sizeof(char*));
    for(int i=0;i<ITER;i++)
    {
        char* buffer;
        A[i]=(char*)malloc(BUFFER_SIZE*sizeof(char));
        printf("adresses - %p\n", A[i]);
        sleep(1);
    }
    for(int i=0;i<ITER;i++)
    {
        free(A[i]);
    }
    free(A);
}

void add_pages()
{
    char* addr = mmap(NULL, PAGE_SIZE*10, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); 
    if (addr == MAP_FAILED)
    {
        printf("mmap erorr!\n");
        return;
    }
    printf("mmap sucses!\n");

    sleep(3);

    /*int ret_val=mprotect(addr, PAGE_SIZE*10, PROT_READ);

    if (ret_val)
    {
        printf("mprotect erorr!\n");
        return;
    }
    printf("mprotect sucses!\n");*/

    sleep(3);

    //*addr=10;

    //*addr;

    //printf("%d - ", tmp);

    printf("luck\n");

    addr[5*PAGE_SIZE+10]=11;


    int ret_val2 = munmap(addr+4*PAGE_SIZE, 3*PAGE_SIZE);

    if(ret_val2 != 0){
        printf("munmap erorr!\n");
        return;
    }
    printf("munmap sucses!\n");

    sleep(10);

    int ret_val3 = munmap(addr, 10*PAGE_SIZE);

    if(ret_val3 != 0){
        printf("last munmap erorr!\n");
        return;
    }
    printf("last munmap sucses!\n");
}

int main(int argc,char *argv[]) {
  
  pid_t pid = getpid();
  printf("pid: %d\n", pid);

  //recur_alloc();

  sleep(10);
  signal(SIGSEGV, sig_handler);

  add_pages();

  sleep(200000);
  //alloc_in_heap();

  return 0;
}