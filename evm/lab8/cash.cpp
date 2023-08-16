#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <time.h>

int *A;

void pryamoy(int *arr, int n)
{
    for(int i=0;i<n;i++){
        arr[i]=i+1;
    }
    arr[n-1]=0;
}

void obrat(int *arr, int n)
{
    for(int i=0;i<n;i++){
        arr[i]=i-1;
    }
    arr[0]=n-1;
}

void random(int *arr, int n)
{
    int *visited;
    visited=(int*)calloc(n, sizeof(int));
    for(int i=0;i<n;i++){
        arr[i]=0;
    }
    int ind;
    visited[0]=1;
    int j=0;
    for(int i=0;i<n-1;i++){
        visited[j]=1;
        while(1){
         ind = rand() % n;
         if(visited[ind]==0){
            break;
         }
        }
        arr[j]=ind;
        j=ind;
    }
}
void progrev(int *arr, int n){
    int j=0;
    for(int i=0;i<n;i++){
        j=arr[j];
    }
}

unsigned long long count(int *arr, int n)
{
    union ticks{
    unsigned long long t64;
    struct s32 { long th, tl; } t32;
    } start, end;

    unsigned long long min=2199023255244;
    for(int ii=0;ii<4;ii++){
    asm volatile("rdtsc\n":"=a"(start.t32.th),"=d"(start.t32.tl));
    int j=0;
    for(int i=0;i<n;i++){
        j=arr[j];
    }
    asm volatile("rdtsc\n":"=a"(end.t32.th),"=d"(end.t32.tl));

    unsigned long long result = (end.t64 - start.t64) / n;
    if(result<min){
        min=result;
    }
}
    return min;
}
void print(int *arr, int n){
    for(int i=0;i<n;i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("\n");
}

int main()
{
    for(int i=256;i<=8388608;i=i*2)
    {
        srand(time(NULL));

        
        A=(int*)calloc(i, sizeof(int));
        pryamoy(A, i);
        for(int j=0;j<100;j++)
        {
        //progrev(A, i);
        }

        std::cout<<"i - "<<i<<" results- "<<count(A, i);

        obrat(A, i);
        for(int j=0;j<100;j++)
        {
        //progrev(A, i);
        }
        std::cout<<" "<<count(A, i);

        random(A, i);
        for(int j=0;j<100;j++)
        {
        //progrev(A, i);
        }
        std::cout<<" "<<count(A, i)<<std::endl;

        free(A);
    }

    return 0;
}
