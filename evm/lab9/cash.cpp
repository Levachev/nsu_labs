#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <time.h>

int offset_size=(24*1024*1024)/4;
int cash_size=(3*1024*1024+64*1024+512*1024)/4;
int arr_size=64*24*1024*1024/4;

int *A;

void obhod(int *arr, int n)
{
    int fragment=cash_size/n;
    for(int i=0; i<fragment; i++)
    {
        for(int j=0; j<n-1; j++)
        {

            arr[i+offset_size*j]=i+offset_size*(j+1);
        }
        arr[i+offset_size*(n-1)]=i+1;
    }
    arr[fragment-1 + offset_size*(n-1)]=0;
}
unsigned long long count(int *arr, int n)
{
    union ticks
    {
        unsigned long long t64;
        struct s32
        {
            long th, tl;
        } t32;
    } start, end;

    unsigned long long min=2199023255244;
    for(int ii=0; ii<4; ii++)
    {
        asm volatile("rdtsc\n":"=a"(start.t32.th),"=d"(start.t32.tl));
        int j=0;
        for(int i=0; i<cash_size; i++)
        {
            j=arr[j];
        }
        asm volatile("rdtsc\n":"=a"(end.t32.th),"=d"(end.t32.tl));

        unsigned long long result = (end.t64 - start.t64) / (cash_size);
        if(result<min)
        {
            min=result;
        }
    }
    return min;
}
void print(int *arr, int n)
{
    for(int i=0; i<n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("\n");
}

int main()
{
    A=(int*)calloc(arr_size, sizeof(int));

    for(int i=1; i<=64; i++)
    {
        obhod(A, i);
        //std::cout<<"tut"<<std::endl;
        std::cout<<"i - "<<i<<" results- "<<count(A, i)<<std::endl;
        //std::cout<<"tut2"<<std::endl;
    }
    free(A);

    return 0;
}
