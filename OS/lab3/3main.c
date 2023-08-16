#include <dirent.h> 
#include <stdio.h> 
#include <stdint.h> 
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define PAGE_SIZE 4096
#define FIRST 140691398795264
#define SECOND 140691405500416

void printf_file(char* file_name)
{

  FILE *f1 = fopen(file_name, "rb");

  if(f1==NULL)
  {
    printf("permission of this file -%s is denied\n", file_name);
    return;
  }

  uint64_t input;

  fseek(f1, (140149793722368 / PAGE_SIZE) * sizeof(uint64_t), SEEK_SET);

  while(1)
  {
    if(ftell(f1)==(140149793783808 / PAGE_SIZE) * sizeof(uint64_t)){
      break;
    }
    fread(&input, sizeof(uint64_t), 1, f1);
    if(!feof(f1))
    {
      //if(input!=0)
      //{
       printf("%ld\n", input);
       uint64_t tmp = input & ((1ULL<< 55) - 1);
       printf("%ld\n", tmp);
      //}
    }
    else
    {
      break;
    }
  }
  printf("\n");
  fclose(f1);
}


int main(int argc,char *argv[]) {

  /*if(argc < 2)
  {
    printf("you have to write file name name, error!");
    return 0 ;
  }*/

  printf_file("/proc/2895/pagemap");
  return 0;
}