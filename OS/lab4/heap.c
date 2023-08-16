#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <signal.h>

#define PAGE_SIZE 4096
#define HEADER_SIZE sizeof(struct header)


void* my_heap=NULL;


int end_of_heap = 0;


void* first_block=NULL;


struct header
{
    int size;
    struct header *next;
    int free;
};


struct header* get_free_block(struct header** last, int size)
{
    struct header* current = first_block;
    while (current && !(current->free && current->size >= size))
    {
        *last = current;
        current = current->next;
    }
    return current;
}


struct header *request_block(int size)
{
    struct header *last = NULL;
    struct header *block = get_free_block(&last, size);
    if (block)
    {
        block->free = 0;
        return block;
    }
    block = my_heap + end_of_heap;
    end_of_heap += HEADER_SIZE + size;

    if(end_of_heap>PAGE_SIZE*100)
    {
        return NULL;
    }

    if (last)
    {
        last->next = block;
    }
    else
    {
        first_block = block;
    }
    block->free = 0;
    block->next = NULL;
    block->size = size;
    return block;
}


void *my_malloc(int size)
{
    struct header *block = request_block(size);
    return block + HEADER_SIZE;
}

void uniting(void *ptr)
{
    struct header *block=ptr-HEADER_SIZE;
    if(block->next->free==1 && block->next)
    {
        block->size=block->size+HEADER_SIZE+block->next->size;
    }
}

void my_free(void *ptr)
{
    struct header *block=ptr-HEADER_SIZE;
    block->free = 1;
    uniting(ptr);
}


int add_pages()
{
    my_heap = mmap(NULL, PAGE_SIZE*100, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); 
    if (my_heap == MAP_FAILED)
    {
        printf("mmap erorr!\n");
        return 0;
    }
    printf("mmap sucses!\n");
    return 1;

}

int main(int argc,char *argv[]) {
  
  pid_t pid = getpid();
  printf("pid: %d\n", pid);

  sleep(20);

  if(!add_pages())
  {
    return 0;
  }

  char* A=(char*)my_malloc(4*sizeof(char));

  if(A!=NULL)
  {
    printf("my_malloc sucses\n");
  }
  A[0]='i';
  printf("%c\n", A[0]);
  my_free(A);
  printf("%c\n", A[0]);

  return 0;
}