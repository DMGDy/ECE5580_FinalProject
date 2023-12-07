#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h> // For AVX intrinsics

/**
 * @brief Multiplies two matrices using AVX instructions.
 * 
 * @param a First matrix
 * @param b Second matrix
 * @param result Result matrix
 * @param n Size of the matrices
 */
void multiply_matrices(float** a, float** b, float** result, int n)
{
    __m256 rowA, elementB, prod, sum;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum = _mm256_setzero_ps(); // Zero out the sum for each cell

            for (int k = 0; k < n; k += 8) {
                // Load 8 elements of a row from matrix A
                rowA = _mm256_loadu_ps(&a[i][k]);

                // Load and broadcast each element of a column from matrix B
                for (int l = 0; l < 8; l++) {
                    elementB = _mm256_set1_ps(b[k + l][j]);
                    prod = _mm256_mul_ps(rowA, elementB);
                    sum = _mm256_add_ps(sum, prod);
                }
            }

            // Store the sum of products in the result matrix
            float temp[8];
            _mm256_storeu_ps(temp, sum);
            for (int l = 0; l < 8; l++) {
                result[i][j] += temp[l];
            }
        }
    }
}

/**
 * @brief Allocates memory for a matrix.
 * 
 * @param n Size of the matrix
 * @return float** Pointer to the allocated matrix
 */
float** allocate_matrix(int n)
{
    float** mat = (float**)malloc(n * sizeof(float*));
    for (int i = 0; i < n; i++) {
        mat[i] = (float*)aligned_alloc(32, n * sizeof(float));
    }
    return mat;
}

/**
 * @brief Frees memory allocated for a matrix.
 * 
 * @param mat Matrix to free
 * @param n Size of the matrix
 */
void free_matrix(float** mat, int n)
{
    for (int i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
}

/**
 * @brief Main function to demonstrate matrix multiplication.
 * 
 * @param argc Argument count
 * @param argv Argument vector
 * @return int Program exit status
 */
int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <matrix size>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0 || n % 8 != 0) {
        fprintf(stderr, "Matrix size must be a positive multiple of 8.\n");
        return 1;
    }

    float** matA = allocate_matrix(n);
    float** matB = allocate_matrix(n);
    float** matResult = allocate_matrix(n);

    // Initialize matrices with some values
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matA[i][j] = (float)(rand() % 100) / 10.0f; // Random values for simplicity
            matB[i][j] = (float)(rand() % 100) / 10.0f;
            matResult[i][j] = 0.0f;
        }
    }

    // Perform matrix multiplication
    multiply_matrices(matA, matB, matResult, n);

    // Free the allocated memory
    free_matrix(matA, n);
    free_matrix(matB, n);
    free_matrix(matResult, n);

    return 0;
}

