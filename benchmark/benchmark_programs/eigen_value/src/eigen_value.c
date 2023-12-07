#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <immintrin.h> // For AVX intrinsics
#include <time.h>

#define MAX_ITERATIONS 1000
#define EPSILON 1e-9

/**
 * @brief Allocates memory for a matrix.
 * 
 * @param n Size of the matrix
 * @return float** Pointer to the allocated matrix
 */
float**
allocate_matrix(int n) {
    float** mat = (float**)malloc(n * sizeof(float*));
    for (int i = 0; i < n; i++) {
        mat[i] = (float*)aligned_alloc(32, n * sizeof(float)); // 32-byte alignment for AVX
    }
    return mat;
}

/**
 * @brief Frees memory allocated for a matrix.
 * 
 * @param mat Matrix to free
 * @param n Size of the matrix
 */
void 
free_matrix(float** mat, int n) {
    for (int i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
}

/**
 * @brief Multiplies a matrix with a vector using AVX instructions.
 * 
 * @param mat Matrix
 * @param vec Vector
 * @param result Resultant vector
 * @param n Size of the matrix and vectors
 */
void 
multiply_matrix_vector(float** mat, float* vec, float* result, int n) {
    for (int i = 0; i < n; i++) {
        __m256 sum = _mm256_setzero_ps();
        for (int j = 0; j < n; j += 8) {
            __m256 mat_row = _mm256_loadu_ps(&mat[i][j]);
            __m256 vec_col = _mm256_loadu_ps(&vec[j]);
            __m256 prod = _mm256_mul_ps(mat_row, vec_col);
            sum = _mm256_add_ps(sum, prod);
        }
        result[i] = 0;
        for (int k = 0; k < 8; k++) {
            result[i] += ((float*)&sum)[k];
        }
    }
}
/**
 * @brief Normalizes a vector.
 * 
 * @param vec The vector to normalize
 * @param n The size of the vector
 */
void 
normalize_vector(float* vec, int n) {
    float sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += vec[i] * vec[i];
    }
    float norm = sqrt(sum);
    for (int i = 0; i < n; i++) {
        vec[i] /= norm;
    }
}

/**
 * @brief Generates a random nxn matrix.
 * 
 * @param mat The matrix to fill with random values
 * @param n The size of the matrix
 */
void 
generate_random_matrix(float** mat, int n) {
    srand(time(NULL)); // Seed the random number generator

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = ((float)rand() / (float)(RAND_MAX)) * 10.0; // Random float between 0 and 10
        }
    }
}
int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size of the matrix>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 2 || n % 8 != 0) {
        fprintf(stderr, "Matrix size must be greater than 2 and a multiple of 8.\n");
        return 1;
    }

    // Allocate and initialize the matrix and vectors
    float** mat = allocate_matrix(n);
    float* vec = (float*)aligned_alloc(32, n * sizeof(float));
    float* result = (float*)aligned_alloc(32, n * sizeof(float));

    // Initialize matrix and vector with some values (can be randomized or specific)
    // ...
    generate_random_matrix(mat, n);
    // Initialize the vector with some values
    srand(time(NULL));
    for (int i = 0; i < n; i++) 
    {
      vec[i] = ((float)rand() / (float)(RAND_MAX)) * 10.0;
    }

    // Power Iteration Algorithm
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        multiply_matrix_vector(mat, vec, result, n);
        normalize_vector(result, n);

        // Check for convergence
        float diff = 0.0;
        for (int j = 0; j < n; j++) {
            diff += fabs(result[j] - vec[j]);
        }

        if (diff < EPSILON) {
            break;
        }

        // Prepare for next iteration
        for (int j = 0; j < n; j++) {
            vec[j] = result[j];
        }
    }

    // The largest eigenvalue is approximately the norm of the result vector
    float eigenvalue = 0.0;
    for (int i = 0; i < n; i++) {
        eigenvalue += result[i] * result[i];
    }
    eigenvalue = sqrt(eigenvalue);

    printf("Approximate largest eigenvalue: %f\n", eigenvalue);

    // Clean up
    free_matrix(mat, n);
    free(vec);
    free(result);

    return 0;
}

