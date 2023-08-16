#include <dirent.h> 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void create_file(char* file_name)
{
  int fd = open(file_name, O_RDWR|O_CREAT, 0777);
  if(fd==-1)
  {
    printf("cant create file, error!");
  }
  close(fd);
}

void create_dir(char* dir_name)
{
  mkdir(dir_name, 0777);
}

void create_soft_link(char* file_name, char* link_name)
{
  int ret_val=symlink(file_name, link_name);
  if(ret_val==-1)
  {
    printf("cant create soft link, error!");
  }
}

void create_hard_link(char* file_name, char* link_name)
{
  int ret_val=link(file_name, link_name);
  if(ret_val==-1)
  {
    printf("cant create hard link, error!");
  }
}

void print_dir(char* dir_name)
{
  DIR* d;

  struct dirent* dir;
  d = opendir(dir_name);
  if (d) 
  {
    while ((dir = readdir(d)) != NULL) {
      if(dir->d_type != DT_DIR)
      {
        printf("%s\n", dir->d_name);
      }
    }
    closedir(d);
  }
}

char* get_original_dir_name(char* dir_name)
{
  int len=strlen(dir_name);
  if(dir_name[len-1]=='/')
  {
    return dir_name;
  }
  else
  {
    char* result = (char*)calloc(len+2, sizeof(char));
    for (int i = 0; i < len; ++i)
    {
      result[i]=dir_name[i];
    }
    result[len]='/';
    result[len+1]='\0';
    return result;
  }
}

char* get_file_name(char* first_part, char* second_part)
{
  char *result = malloc(strlen(first_part)+strlen(second_part)+1);

  strcpy(result, first_part);
  strcat(result, second_part);

  return result;
}

char* get_dir_name(char* first_part, char* second_part)
{
  int len=strlen(first_part)+strlen(second_part)+2;
  char *result = malloc(strlen(first_part)+strlen(second_part)+2);

  strcpy(result, first_part);
  strcat(result, second_part);
  result[len-2]='/';
  result[len-1]='\0';

  return result;
}

void delete_file(char* file_name)
{
  if (unlink(file_name)==-1)
  {
    printf("Cannot remove file - %s\n", file_name);
  }
}

void delete_soft_link(char* link_name)
{
  if (unlink(link_name)==-1)
  {
    printf("Cannot remove soft link - %s\n", link_name);
  }
}

void delete_hard_link(char* link_name)
{
  if (unlink(link_name)==-1)
  {
    printf("Cannot remove hard link - %s\n", link_name);
  }
}

void delete_dir(char* dir_name)
{
  DIR* d;

  struct dirent* dir;
  d = opendir(dir_name);
  if (d) 
  {
    while ((dir = readdir(d)) != NULL) {
      if(dir->d_type == DT_DIR)
      {
        if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))
        {
          continue;
        }
        delete_dir(get_dir_name(dir_name, dir->d_name));
      }
      else
      {
        delete_file(get_file_name(dir_name, dir->d_name));
      }
    }
    closedir(d);
  }
  rmdir(dir_name);
}

void printf_file(char* file_name)
{
  FILE *f1 = fopen(file_name, "rb");

  if(f1==NULL)
  {
    printf("permission of this file -%s is denied\n", file_name);
    return;
  }

  char input;

  while(1)
  {
    fread(&input, 1, 1, f1);
    if(!feof(f1))
    {
      printf("%d", input);
    }
    else
    {
      break;
    }
  }
  printf("\n");
  fclose(f1);
}

char* print_soft_link(char* link_name)
{
  char* buf = (char*)malloc(1024);
  int len = readlink(link_name, buf, 1024);

  if(len==-1)
  {
    printf("Cannot print soft link - %s\n", link_name);
    return NULL;
  }

  buf[len] = '\0';
  //printf("%s\n", buf);
  return buf;
}

void print_soft_link_content(char* link_name)
{
  char* file_name=print_soft_link(link_name);
  if(file_name==NULL)
  {
    printf("Cannot print soft link content - %s\n", link_name);
    return;
  }
  printf_file(file_name);
  free(file_name);
}

void get_stats(char* file_name)
{
  struct stat st;
  if(stat(file_name, &st)==-1)
  {
    printf("cant get permissions, error!");
    return;
  }
  if((st.st_mode & S_IRUSR))
  {
    printf("r");
  }
  else
  {
    printf("-");
  }
  if((st.st_mode & S_IWUSR))
  {
    printf("w");
  }
  else
  {
    printf("-");
  }
  if((st.st_mode & S_IXUSR))
  {
    printf("x");
  }
  else
  {
    printf("-");
  }

  if((st.st_mode & S_IRGRP))
  {
    printf("r");
  }
  else
  {
    printf("-");
  }
  if((st.st_mode & S_IWGRP))
  {
    printf("w");
  }
  else
  {
    printf("-");
  }
  if((st.st_mode & S_IXGRP))
  {
    printf("x");
  }
  else
  {
    printf("-");
  }

  if((st.st_mode & S_IROTH))
  {
    printf("r");
  }
  else
  {
    printf("-");
  }
  if((st.st_mode & S_IWOTH))
  {
    printf("w");
  }
  else
  {
    printf("-");
  }
  if((st.st_mode & S_IXOTH))
  {
    printf("x");
  }
  else
  {
    printf("-");
  }
  printf("\n");
  printf("number of hard links - %ld\n", st.st_nlink);
}

void set_permis(char* file_name, char* parametrs)
{
  char *end;
  if(chmod(file_name, strtol(parametrs, &end, 8))==-1)
  {
    printf("cant set permissions, error!");
    return;
  }
}

int main(int argc,char *argv[]) {

  if(argc < 2)
  {
    printf("you have to write directory name, error!");
    return 0 ;
  }

  char* original_dir_name = get_original_dir_name(argv[1]);

  //create_dir(original_dir_name);

  //print_dir(original_dir_name);

  //delete_file(argv[1]);

  //delete_dir(original_dir_name);

  //create_file(argv[1]);

  //printf_file(argv[1]);

  //create_soft_link(argv[1], argv[2]);

  //create_hard_link(argv[1], argv[2]);

  //delete_hard_link(argv[1]);
  
  /*char* soft_link_target=print_soft_link(argv[1]);
  printf("%s\n", soft_link_target);
  free(soft_link_target);*/

  //print_soft_link_content(argv[1]);

  //delete_soft_link(argv[1]);

  get_stats(argv[1]);

  //set_permis(argv[1], argv[2]);

  return 0;
}