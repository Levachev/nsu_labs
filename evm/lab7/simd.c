#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <xmmintrin.h>

#define M 10000
#define N 16

float **A;
float **B;
float **R;
float **I;
float **tmp;
float **tmp2;
float **Res;

void print(float **arr1)
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            printf("%f ", arr1[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
}

void make_mat(float **arr)
{
    for(int i=0; i<N; i++)
    {
        arr[i]=(float*)calloc(N, sizeof(float));
    }
}

void free_mat(float **a)
{
    for(int i=0; i<N; i++)
    {
        free(a[i]);
    }
    free(a);
}
 
void assignment(float **arr1, float **arr2)
{

for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            arr1[i][j]=arr2[i][j];
        }
    }



    /*__m128 *xx, *yy;
    __m128 p;

    for(int i=0; i<N; i++)
    {
        xx = (__m128*)(arr2[i]);
        for(int i1=0; i1<N/4; ++i1)
        {
            p = xx[i1];
            _mm_store_ps(&arr1[i][4*i1], xx[i1]);
        }
    }*/
}

void trans(float **arr)
{
    float **temp=(float**)calloc(N,sizeof(float*));
    make_mat(temp);
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            temp[i][j]=arr[j][i];
        }
    }
    assignment(arr, temp);
    free_mat(temp);
}

void mul(float **arr1, float **arr2, float **r)
{
    trans(arr2);

    __m128 *xx, *yy;
    __m128 p, s;

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            xx = (__m128*)(arr1[i]);
            yy = (__m128*)(arr2[j]);

            s = _mm_setzero_ps();
            for(int i1=0; i1<N/4; ++i1)
            {
                p = _mm_mul_ps(xx[i1],yy[i1]);
                s = _mm_add_ps(s,p);
            }
            p = _mm_movehl_ps(p,s);
            s = _mm_add_ps(s,p);
            p = _mm_shuffle_ps(s,s,1);
            s = _mm_add_ss(s,p);
            float sum;
            _mm_store_ss(&sum,s);
            //printf("%f\n", sum);
            r[i][j]=sum;
        }
    }
    trans(arr2);
}

void plus(float **arr1, float **arr2, float **r)
{
for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            r[i][j]=arr1[i][j]+arr2[i][j];
        }
    }

    /*__m128 *xx, *yy;
    __m128 p, s;

    for(int i=0; i<N; i++)
    {
        xx = (__m128*)(arr1[i]);
        yy = (__m128*)(arr2[i]);

        for(int i1=0; i1<N/4; ++i1)
        {
            //r[i][j]=arr1[i][j]+arr2[i][j];
            p = _mm_add_ps(xx[i1], yy[i1]);
            _mm_store_ps(&r[i][4*i1], p);
        }
    }*/
}

void minus(float **arr1, float **arr2, float **r)
{
    __m128 *xx, *yy;
    __m128 p, s;

    for(int i=0; i<N; i++)
    {
        xx = (__m128*)(arr1[i]);
        yy = (__m128*)(arr2[i]);

        for(int i1=0; i1<N/4; ++i1)
        {
            //r[i][j]=arr1[i][j]+arr2[i][j];
            p = _mm_sub_ps(xx[i1], yy[i1]);
            _mm_store_ps(&r[i][4*i1], p);
        }
    }
}

int main()
{

    A=(float**)calloc(N,sizeof(float*));
    B=(float**)calloc(N,sizeof(float*));
    R=(float**)calloc(N,sizeof(float*));
    I=(float**)calloc(N,sizeof(float*));
    tmp=(float**)calloc(N,sizeof(float*));
    tmp2=(float**)calloc(N,sizeof(float*));
    Res=(float**)calloc(N,sizeof(float*));

    make_mat(A);
    make_mat(B);
    make_mat(R);
    make_mat(I);
    make_mat(tmp);
    make_mat(tmp2);
    make_mat(Res);

    struct timespec start, end;

    srand(time(NULL));
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    float max2=-1, max1=-1;
    for(int i=0; i<N; i++)
    {
        float sum=0;
        for(int j=0; j<N; j++)
        {
            Res[i][j]=0;
            I[i][j]=0;
            if(i==j)
            {
                I[i][j]=1;
            }
            A[i][j]=(i>=j);
            //A[i][j]=(float)(rand()% 100 + 1);
            sum+=fabs(A[i][j]);
        }
        if(max2<sum)
        {
            max2=sum;
        }
    }
    //print(A);


    for(int j=0; j<N; j++)
    {
        float sum=0;
        for(int i=0; i<N; i++)
        {
            sum+=fabs(A[i][j]);
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
            B[i][j]=A[j][i]/(max1*max2);
            //B[i*N+j]=B[i*N+j]/(max1*max2);
        }
    }

    //print(B);
    mul(B, A, tmp);
    //print(tmp);
    minus(I, tmp, tmp2);
    //print(tmp2);
    assignment(R, tmp2);
    assignment(Res, I);
    assignment(tmp2, R);

    for(int i=1; i<M; i++)
    {
        //print(Res);
        plus(Res, R, tmp);
        assignment(Res, tmp);

        mul(R, tmp2, tmp);
        assignment(R, tmp);
    }
    //print(Res);
    //print(B);
    mul(Res, B, tmp);
    //print(tmp);

    assignment(Res, tmp);


    //print(Res);
    //print(A);

    mul(A, Res, tmp);
    //print(tmp);

    max2=-1;
    max1=-1;

    for(int i=0; i<N; i++)
    {
        float sum=0;
        for(int j=0; j<N; j++)
        {
            sum+=fabs(tmp[i][j]);
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
            sum+=fabs(tmp[i][j]);
        }
        if(max1<sum)
        {
            max1=sum;
        }
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    printf("Time taken read: %lf sec.\n",end.tv_sec-start.tv_sec+ 0.000000001*(end.tv_nsec-start.tv_nsec));
    printf("%f %f\n", max1, max2);

    free_mat(A);
    free_mat(B);
    free_mat(R);
    free_mat(I);
    free_mat(tmp);
    free_mat(tmp2);
    free_mat(Res);

    return 0;
}

