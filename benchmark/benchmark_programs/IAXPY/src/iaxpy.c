#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>

int
main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <vector_size>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    float *X = (float*)_mm_malloc(n * sizeof(float), 32); // 32-byte aligned for AVX
    float *Y = (float*)_mm_malloc(n * sizeof(float), 32);
    
    // Initialize vectors and scalar
    float a = 2.0f;
    for(int i = 0; i < n; i++) {
        X[i] = rand();
        Y[i] = rand();
    }

    // IAXPY loop
    for(int i = 0; i < n; i += 8) {
        __m256 x_vec = _mm256_load_ps(&X[i]);
        __m256 y_vec = _mm256_load_ps(&Y[i]);
        __m256 a_vec = _mm256_set1_ps(a);
        __m256 result = _mm256_add_ps(_mm256_mul_ps(a_vec, x_vec), y_vec);
        _mm256_store_ps(&Y[i], result);
    }

    // Optionally print result
    // for(int i = 0; i < n; i++) {
    //     printf("%f ", Y[i]);
    // }

    _mm_free(X);
    _mm_free(Y);

    return 0;
}
