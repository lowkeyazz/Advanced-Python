#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 200
#define SIZE_OF 8
#define SEED 86456

void matmul(int block_size);

int main() {
    int block_sizes[] = {1, 2, 5, 10,20};  // Different block sizes to test
    int num_block_sizes = sizeof(block_sizes) / sizeof(block_sizes[0]);

    for (int i = 0; i < num_block_sizes; i++) {
        printf("Block size: %d\n", block_sizes[i]);
        printf("a");
        matmul(block_sizes[i]);
        printf("\n");
    }

    return 0;
}

void matmul(int block_size) {
    FILE *file;
    file = fopen("plotm.csv", "a+");
    int i, j, k;
    double x[N][N], y[N][N], z[N][N];
    double msec, rate;
    double start, finish;
    srand(SEED);

    // Initialize matrices
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            x[i][j] = ((double)rand() / RAND_MAX) + 1.0;
            y[i][j] = ((double)rand() / RAND_MAX) + 1.0;
        }
    }

    start = (double)clock()/ (double) CLOCKS_PER_SEC;

    // Matrix multiplication with block size
    for (i = 0; i < N; i += block_size) {
        for (j = 0; j < N; j += block_size) {
            for (k = 0; k < N; k += block_size) {
                for (int ii = i; ii < i + block_size; ii++) {
                    for (int jj = j; jj < j + block_size; jj++) {
                        for (int kk = k; kk < k + block_size; kk++) {
                            z[ii][jj] += x[ii][kk] * y[kk][jj];
                        }
                    }
                }
            }
        }
    }

    finish = (double)clock()/ (double) CLOCKS_PER_SEC;

    msec = (finish - start) *1000.0;
    rate = sizeof(double) * N * (1000.0 / msec) / (1024*1024);
    printf("CPU Time: %.3f milliseconds\n", msec);
    printf("Bandwidth: %.3f GB/s\n", rate);
    fprintf(file, "%.3f,\n",msec);
    fprintf(file, "%.3f,\n",rate);
}
