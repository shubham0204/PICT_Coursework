#include <cuda_runtime.h>
#include <iostream>


/*
cudaMalloc ( void** devPtr, size_t size )
Allocate memory on the device.

cudaMemcpy ( void* dst, const void* src, size_t count, cudaMemcpyKind kind )
Copies data between host and device.

cudaFree ( void* devPtr )
Frees memory on the device.
*/

// number of floats in the vector
#define N 256

/*
- the kernel which adds two vector elements
and stores the sum in another vector
- the __global__ specifier indicates that the function
can be called from either CPU or GPU memory, but executes
on the GPU always
*/
__global__ void vec_item_add(const float* vec1, const float* vec2, float* sum) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N)
        sum[i] = vec1[i] + vec2[i];
}

int main() {
    // size of the vector in bytes
    int vec_size_bytes = N * sizeof(float);

    // (1) initialize three vecs in host (CPU) memory
    float* vec1 = (float*)malloc(vec_size_bytes);
    float* vec2 = (float*)malloc(vec_size_bytes);
    float* sum = (float*)malloc(vec_size_bytes);
    for (int i = 0; i < N; i++) {
        vec1[i] = 2.9f;
        vec2[i] = -3.4f;
    }

    // (2) initialize three vecs in device (GPU) memory
    float* gpu_vec1;
    float* gpu_vec2;
    float* gpu_sum;
    cudaMalloc(&gpu_vec1, vec_size_bytes);
    cudaMalloc(&gpu_vec2, vec_size_bytes);
    cudaMalloc(&gpu_sum, vec_size_bytes);

    // (3) copy contents from vectors present in the host memory
    //     to vectors present in the device memory
    cudaMemcpy(gpu_vec1, vec1, vec_size_bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(gpu_vec2, vec2, vec_size_bytes, cudaMemcpyHostToDevice);

    // (4) execute the kernel on the GPU device with given no. of blocks
    //     and threads; also copy the contents of the sum vector from the GPU
    //     memory to the sum vector present in the CPU memory
    int n_threads = 16;
    int n_blocks = N / n_threads;
    vec_item_add<<<n_blocks, n_threads>>>(gpu_vec1, gpu_vec2, gpu_sum);
    cudaMemcpy(sum, gpu_sum, vec_size_bytes, cudaMemcpyDeviceToHost);

    // (5) print the contents of the sum vector present in the host memory
    for (int i = 0; i < N; i++) {
        printf("%f ", sum[i]);
    }
    printf("\n");

    // (6) deallocate memory from CPU and GPU devices
    free(vec1);
    free(vec2);
    free(sum);
    cudaFree(gpu_vec1);
    cudaFree(gpu_vec2);
    cudaFree(gpu_sum);    
    return 0;
}
