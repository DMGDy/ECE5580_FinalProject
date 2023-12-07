#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include <pthread.h>

void print_m256(__m256); 
void multiply_matrices(float*,float*,float*,int);


void
multiply_matrices(float *A, float *B, float *C, int n) {
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j += 8)
        { 
            // Process 8 elements at a time
            volatile __m256 sum = _mm256_setzero_ps(); // Initialize sum vector to 0
            for (int k = 0; k < n; k++) 
            {
                volatile __m256 a_vec = _mm256_set1_ps(A[i * n + k]);
                volatile __m256 b_vec = _mm256_loadu_ps(&B[k * n + j]);
                sum = _mm256_add_ps(sum, _mm256_mul_ps(a_vec, b_vec));
            }

            _mm256_storeu_ps(&C[i * n + j], sum);
        }
    }
}

void 
print_m256(__m256 var) {
    // Create an array to store the elements of __m256
    float arr[8];
    
    // Store the elements of var into the array
    _mm256_storeu_ps(arr, var);
    
    // Print each element
    printf("Elements of __m256: ");
    for (int i = 0; i < 8; ++i) {
        printf("%f \t", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <matrix_size>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    float *A = (float*)_mm_malloc(n * n * sizeof(float), 32);
    float *B = (float*)_mm_malloc(n * n * sizeof(float), 32);
    float *C = (float*)_mm_malloc(n * n * sizeof(float), 32);

    // Initialize matrices A and B with some values
    for (int i = 0; i < n * n; i++) {
        A[i] = rand()%100;
        B[i] = rand()%100;
    }

    multiply_matrices(A, B, C, n);

    // Optionally print result matrix C
    // for (int i = 0; i < n * n; i++) {
    //     if (i % n == 0) printf("\n");
    //     printf("%f ", C[i]);
    // }

    _mm_free(A);
    _mm_free(B);
    _mm_free(C);

    return 0;
}

