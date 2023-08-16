#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include"cblas.h"
//#include "mkl.h"

#define M 100000
#define N 16

float *A;
float *B;
float *R;
float *I;
float *tmp;
float *tmp2;
float *Res;

void mul(float *arr1, float *arr2, float *r)
{
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, arr1, N, arr2, N, 0.0 , r, N);
}

void plus(float *arr1, float *arr2, float *r)
{
           cblas_scopy(N*N, arr2, 1, r, 1);
           cblas_saxpy(N*N, 1.0, arr1, 1, r, 1); 
}

void minus(float *arr1, float *arr2, float *r)
{
           cblas_scopy(N*N, arr1, 1, r, 1);
           cblas_saxpy(N*N, -1.0, arr2, 1, r, 1); 
}

void assignment(float *arr1, float *arr2)
{
    cblas_scopy(N*N, arr2, 1, arr1, 1);
}

void print(float *arr1)
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            printf("%f ", arr1[i*N+j]);
        }
        printf("\n");
    }
}

int main()
{
    A=(float*)calloc(N*N, sizeof(float));
    B=(float*)calloc(N*N, sizeof(float));
    R=(float*)calloc(N*N, sizeof(float));
    I=(float*)calloc(N*N, sizeof(float));
    tmp=(float*)calloc(N*N, sizeof(float));
    tmp2=(float*)calloc(N*N, sizeof(float));
    Res=(float*)calloc(N*N, sizeof(float));

    struct timespec start, end;
    srand(time(NULL));
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    float max2=-1, max1=-1;
    for(int i=0; i<N; i++)
    {
        float sum=0;
        for(int j=0; j<N; j++)
        {
            Res[i*N+j]=0;
            I[i*N+j]=0;
            if(i==j)
            {
                I[i*N+j]=1;
            }
            A[i*N+j] = (i>=j);
            sum+=fabs(A[i*N+j]);
        }
        if(max2<sum)
        {
            max2=sum;
        }
    }
    //print(A);
   // printf("\n");
//print(tmp);
    /*plus(A, B, tmp);
    print(tmp);
minus(tmp, A, tmp2);
printf("\n");
print(tmp2);*/
//print(A);
//printf("\n");

    for(int j=0; j<N; j++)
    {
        float sum=0;
        for(int i=0; i<N; i++)
        {
            sum+=fabs(A[i*N+j]);
        }
        if(max1<sum)
        {
            max1=sum;
        }
    }
    printf("%f %f\n", max1, max2);

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            B[i*N+j]=A[j*N+i]/(max1*max2);
            //B[i*N+j]=B[i*N+j]/(max1*max2);
        }
    }
    //print(B);
    mul(B, A, tmp);
    //print(tmp);
    minus(I, tmp, tmp2);
   // print(tmp2);
    assignment(R, tmp2);
    assignment(Res, I);
    assignment(tmp2, R);

    for(int i=1; i<M; i++)
    {
        //print(R);
        plus(Res, R, tmp);
        assignment(Res, tmp);

        mul(R, tmp2, tmp);
        assignment(R, tmp);
        //printf("%f %f\n", get_norm1(R), get_norm2(R));
    }
   // print(B);
    mul(Res, B, tmp);
    assignment(Res, tmp);

//print(Res);
//printf("\n");

    mul(A, Res, tmp);
    //print(tmp);

    max2=-1;
    max1=-1;

    for(int i=0; i<N; i++)
    {
        float sum=0;
        for(int j=0; j<N; j++)
        {
            sum+=fabs(tmp[i*N+j]);
        }
        //printf("%f\n", sum);
        if(max2<sum)
        {
            max2=sum;
        }
    }

    printf("\n\n");

    for(int j=0; j<N; j++)
    {
        float sum=0;
        for(int i=0; i<N; i++)
        {
            sum+=fabs(tmp[i*N+j]);
        }
        if(max1<sum)
        {
            max1=sum;
        }
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    printf("Time taken read: %lf sec.\n",end.tv_sec-start.tv_sec+ 0.000000001*(end.tv_nsec-start.tv_nsec));
    printf("%f %f\n", max1, max2);

    free(A);
    free(B);
    free(R);
    free(I);
    free(tmp);
    free(tmp2);
    free(Res);

    return 0;
}

