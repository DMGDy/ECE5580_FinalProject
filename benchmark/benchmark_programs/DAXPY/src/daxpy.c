#include <immintrin.h> // AVX intrinsics
#include <stdio.h>

#define SIZE 10

void daxpy_avx(int n, double a, double *x, double *y) {
    // Load the scalar 'a' into all elements of a 256-bit vector
    __m256d a_vec = _mm256_set1_pd(a);

    // Process four elements at a time
    for (int i = 0; i < n; i += 4) {
        // Load four elements of x and y into vectors
        __m256d x_vec = _mm256_loadu_pd(x + i);
        __m256d y_vec = _mm256_loadu_pd(y + i);
        
        // Perform the operation a*x + y
        __m256d result_vec = _mm256_add_pd(_mm256_mul_pd(a_vec, x_vec), y_vec);
        
        // Store the result back into the y array
        _mm256_storeu_pd(y + i, result_vec);
    }
}

int main() {
    const int size = 8; // Example size, must be a multiple of 4 for this example
    double a = 2.0;
    double x[SIZE] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    double y[SIZE] = {10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0};

    daxpy_avx(size, a, x, y);

    return 0;
}
