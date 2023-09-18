#include "HouseholderReduction.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define A(i, j) (A[(i)*N + (j)])

static int counter = 0;

static inline void PrintVector(const double *y, unsigned N) {
  printf("\\left(\\begin{array}{c}");
  for (unsigned j = 0; j < N; j++) {
    fprintf(stdout, " %.2lf %c%c", y[j], "\\ "[j == N - 1],  "\\ "[j == N - 1]);
  }
  printf("\\end{array}\\right)");
}

static inline void PrintMatrix(const double *matrix, unsigned N) {
  printf("\\left(\\begin{array}{ccc}\n");
  for (unsigned i = 0; i < N; i++) {
    for (unsigned j = 0; j < N; j++) {
      fprintf(stdout, "%.2lf %c%c", matrix[i * N + j], "&\\"[j == N - 1], " \\"[j == N - 1]);
    }
    fprintf(stdout, "\n");
  }
  printf("\\end{array}\\right)");
}

static inline void PrintHouseholderInfo(
  const double *A, const double *y, unsigned N,
  unsigned iteration,
  const double* householder_vector,
  const double* householder_matrix
) {
  printf("A^{(%d)}=", iteration);
  PrintMatrix(A, N);

  printf(";\\\n \\mathbf{b}_%d=", iteration);
  PrintVector(y, N);

  printf(";\\\n \\mathbf{w}_%d=", iteration);
  PrintVector(householder_vector, N);

  printf(";\\\n U_{\\mathbf{w}_%d}=", iteration);
  PrintMatrix(householder_matrix, N);

  if (counter++ != 0)
    printf("\\]\n");
  printf("\\[");
}

static int Sign(double value) { if (signbit(value)) return -1; else return 1; }

static void MatrixOnVectorProduct(const double *matrix, const double *vector, unsigned N,
                                  double *result) {
  for (unsigned i = 0; i < N; i++) {
    result[i] = 0.;
    for (unsigned j = 0; j < N; j++) {
      result[i] += matrix[i * N + j] * vector[j];
    }
  }
}

static void FillHouseholderMatrix(double* matrix, const double* vector, unsigned N) {
  for (unsigned i = 0; i < N; ++i) {
    for (unsigned j = 0; j < N; ++j) {
      matrix[i * N + j] = - 2 * vector[i] * vector[j];
    }
  }
  for (unsigned i = 0; i < N; ++i) {
    matrix[i * N + i] += 1.;
  }
}

static void MatrixProduct(const double* lhs, const double* rhs, unsigned N, double* result) {
  for (unsigned i = 0; i < N; ++i) {
    for (unsigned j = 0; j < N; ++j) {
      result[i * N + j] = 0.;
      for (unsigned k = 0; k < N; ++k) {
        result[i * N + j] += lhs[i * N + k] * rhs[k * N + j];
      }
    }
  }
}

int HouseholderReduction(double *A, unsigned N, const double *y, double *x)
{
  unsigned i, j;
  double alpha_j = 0.;
  double* householder_matrix = NULL;
  double* product_matrix = NULL;
  double* product_vector = NULL;
  double* householder_vector = NULL;
  double householder_vector_norm = 0.;

  // TODO: there is no need to hold Householder matrix in memory,
  // because all of the elements are predefined with formula
  householder_matrix = malloc(N * N * sizeof(*householder_matrix));
  product_matrix = malloc(N * N * sizeof(*product_matrix));
  // TODO: there is no need to hold Householder vector in memory separately,
  // we can save into column of matrix A to save space
  householder_vector = malloc(N * sizeof(*householder_vector));
  product_vector = malloc(N * sizeof(*product_vector));
  if (!householder_matrix || !householder_vector || !product_matrix || !product_vector) {
    printf("not enough memory\n");
    free(householder_matrix);
    free(householder_vector);
    free(product_matrix);
    free(product_vector);
    return 1;
  }

  memcpy(x, y, N * sizeof(*x));

  for (j = 0; j < N; ++j)
  {
    alpha_j = 0.;
    for (i = j; i < N; ++i) {
      alpha_j += pow(A(i, j), 2);
    }
    alpha_j = sqrt(alpha_j);

    householder_vector_norm = 0.;
    householder_vector[j] = A(j,j) / alpha_j + Sign(A(j, j));
    householder_vector_norm += pow(householder_vector[j], 2);
  
    memset(householder_vector, 0, j * sizeof(*householder_vector));
    for (i = j + 1; i < N; ++i) {
      householder_vector[i] = A(i,j) / alpha_j;
      householder_vector_norm += pow(householder_vector[i], 2);
    }
    householder_vector_norm = sqrt(householder_vector_norm);
    for (i = j; i < N; ++i) {
      householder_vector[i] /= householder_vector_norm;
    }

    FillHouseholderMatrix(householder_matrix, householder_vector, N);

    MatrixProduct(householder_matrix, A, N, product_matrix);
    MatrixOnVectorProduct(householder_matrix, x, N, product_vector);

    memcpy(A, product_matrix, N * N * sizeof(*A));
    memcpy(x, product_vector, N * sizeof(*x));
  }

  // reverse Gaussian step
  for (j = N; j >= 1; --j) {
    x[j - 1] /= A(j - 1, j - 1);
    A(j - 1, j - 1) = 1.;
    for (i = 0; i < j - 1; i++) {
      x[i] -= A(i, j - 1) * x[j - 1];
      A(i, j - 1) = 0.;
    }
  }

  free(householder_matrix);
  free(householder_vector);
  free(product_matrix);
  free(product_vector);
  return 0;
}
