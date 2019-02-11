
/* File:     mv_mult_mpi.c
 *
 * Purpose:  Implement parallel matrix-vector multiplication using
 *           one-dimensional arrays to store the vectors and the
 *           matrix.  Vectors use block distributions and the
 *           matrix is distributed by block rows.
 *
 * Input:    Rowwise-distributed matrix A and vectors y, x, d,
 * Algorithm:
 * 	     For k=0 to t-1
 * 	          y = d+ Ax
 * 		  x=y
 *    	     Endfor
 * Output:   Process 0 has the final copy of vector x.
 * Notes:     
 *    1. Number of processes should evenly divide both m and n
 *    2. Define DEBUG for verbose output
 *
 * IPP:      Section 3.4.9 (pp. 113 and ff.)
 */
#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"

#define UPPER_TRIANGULAR 1
int itmv_mult_seq (double A[], double x[], double d[], double y[],
               int matrix_type, int n, int t);


int main (int argc, char*argv[])
{

int n=4096; int t=1024;
int i, j; 

  double *A,*B, *x,*d,*y;
  A = malloc (n * n * sizeof (double));
  B = malloc (n * n * sizeof (double));
  x = malloc (n * sizeof (double));
  d = malloc (n * sizeof (double));
  y = malloc (n * sizeof (double));      
  

  // initialize x and d
  for(i=0; i < n; i++) {
    x[i] = 0.0;
    d[i] = (2.0*n-1.0)/n;
  }

    
//A is upper triangular
for(i=0; i<n; i++) {
      for(j=0; j<n; j++) {
        if (i <=j ) {
          A[i*n+j] = 0;
        } else {
          A[i*n+j] = -1.0/n; 
        }
      }
    }

   
///make diagonal one B
    for(i=0; i<n; i++) {
      for(j=0; j<n; j++) {
          if(j == i) {
            B[i*n+j] = 0;
          } else {
            B[i*n+j] = -1.0/n; 
          }
      }
    }
  
//itmv_mult_seq (double A[], double x[], double d[], double y[], int matrix_type, int n, int t)
double startdiagtime= get_time();
itmv_mult_seq(B, x, d, y, !UPPER_TRIANGULAR, n, t);
double enddiagtime= get_time();
 printf ("Program diagonal itmv seq.c: wall clock time = %f seconds\n",
          enddiagtime - startdiagtime);

double starttriangletime= get_time();
itmv_mult_seq(A, x, d, y, UPPER_TRIANGULAR, n, t);
double endtriangletime= get_time();
 printf ("Program triangular time seq.c: wall clock time = %f seconds\n",
          endtriangletime - starttriangletime);


  free (A);
  free (B);
  free (x);
  free (d);
  free(y);
  return 1;
}

/*-------------------------------------------------------------------
 * Function:  itmv_mult_seq
 * Purpose:   Run t iterations of  computation:  {y=d+Ax; x=y} sequentially. 
 * In args:   A:  matrix A
 *            d:  column vector d
 *            matrix_type:  matrix_type=0 means A is a regular matrix. 
 *            		    matrix_type=1 (UPPER_TRIANGULAR) means A is an upper triangular matrix
 *            n:        the global  number of columns (same as the number of rows)
 *            t: 	the number of iterations
 * In/out:    x:  column vector x
 *            y:  column vector y
- * Return:  1  means succesful
 * 	    0  means unsuccessful 
 * Errors:   If an error is detected (e.g. n is non-positive, matrix/vector pointers are NULL. 
 *           
 */
int
itmv_mult_seq (double A[], double x[], double d[], double y[],
               int matrix_type, int n, int t)
{
  int i,
    j,
    start,
    k;

  if (n <= 0 || A == NULL || x == NULL || d == NULL || y == NULL)
    return 0;

  for (k = 0; k < t; k++) {
    for (i = 0; i < n; i++) {
      y[i] = d[i];
      if (matrix_type == UPPER_TRIANGULAR) {
        start = i;
      }
      else {
        start = 0;
      }
      for (j = start; j < n; j++) {
        y[i] += A[i * n + j] * x[j];
      }
    }
    for (i = 0; i < n; i++) {
      x[i] = y[i];
    }
  }
  return 1;
}
