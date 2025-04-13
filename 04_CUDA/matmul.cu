#include <stdio.h>
#include <cuda_runtime.h>

#define M 32
#define K 64
#define N 32
#define SIZE_MAT1 M * K * sizeof(float)
#define SIZE_MAT2 K * N * sizeof(float)
#define SIZE_PROD M * N * sizeof(float)
#define THREAD_BLOCK_SIZE 16

__global__ void matmul(float* mat1, float* mat2, float* prod) {
    int row = threadIdx.x + blockDim.x * blockIdx.x;
    int col = threadIdx.y + blockDim.y * blockIdx.y;
    if (row < M && col < N) {
        float dot_prod = 0.0f;
        for (int k = 0; k < K; k++) {
            dot_prod += mat1[M * row + k] * mat2[k * N + col];
        }
        prod[M * row + col] = dot_prod;
    }
}

void init_const_matrix(float* elements, int n_rows, int n_cols, float c) {
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            elements[i * n_cols + j] = c;
        }
    }
}

int main(void) {
    float* mat1 = (float*) malloc(SIZE_MAT1);
    float* mat2 = (float*) malloc(SIZE_MAT2);
    float* prod = (float*) malloc(SIZE_PROD);
    init_const_matrix(mat1, M, K, 1.0f);
    init_const_matrix(mat2, K, N, 1.0f);

    float* gpu_mat1;
    float* gpu_mat2;
    float* gpu_prod;
    cudaMalloc(&gpu_mat1, SIZE_MAT1);
    cudaMalloc(&gpu_mat2, SIZE_MAT2);
    cudaMalloc(&gpu_prod, SIZE_PROD);

    cudaMemcpy(gpu_mat1, mat1, SIZE_MAT1, cudaMemcpyHostToDevice);
    cudaMemcpy(gpu_mat2, mat2, SIZE_MAT2, cudaMemcpyHostToDevice);

    // (M + THREAD_BLOCK_SIZE - 1) / THREAD_BLOCK_SIZE is equivalent
    // to the ceil division of M by THREAD_BLOCK_SIZE
    dim3 num_blocks((M + THREAD_BLOCK_SIZE - 1) / THREAD_BLOCK_SIZE, 
                    (N + THREAD_BLOCK_SIZE - 1) / THREAD_BLOCK_SIZE);
    dim3 thread_block_size(THREAD_BLOCK_SIZE, THREAD_BLOCK_SIZE);
    matmul<<<num_blocks, thread_block_size>>>(gpu_mat1, gpu_mat2, gpu_prod);
    cudaMemcpy(prod, gpu_prod, SIZE_PROD, cudaMemcpyDeviceToHost);

    free(mat1);
    free(mat2);
    free(prod);
    cudaFree(gpu_mat1);
    cudaFree(gpu_mat2);
    cudaFree(gpu_prod);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%f ", prod[i * N + j]);
        }
        printf("\n");
    }
    return 0;
}