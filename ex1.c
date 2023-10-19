#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {  
    double s, e;
    FILE *file;
    file = fopen("plot.csv", "a+");
    int N=1000000;
    double t,rate;
    double mean = 0;
    double *a;
    a = malloc(N*30*sizeof(double));
    for (int i = 0; i < N*30; i++)
    {
        a[i]=i;
    }
    
    for (int j = 1; j <= 30; j++) {
        s = (double)clock()/ (double) CLOCKS_PER_SEC;
        for (int i = 0; i < N*j; i=i+j)
        {
            mean += a[i];
        }
        e = (double)clock()/ (double) CLOCKS_PER_SEC;
        t=(e-s)*1000.0;
        rate = sizeof(double) * N * (1000.0 / t) / (1024*1024);
        printf("stride : %d\n",j);
        printf("Mean: %f\n", mean/N);
        printf("time: %f\n", t);
        printf("rate: %f\n", rate);
        fprintf(file, "%f,\n",t);
        fprintf(file, "%f,\n",rate);
    }
fclose(file);
    return 0;
}