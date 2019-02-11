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
#include <mpi.h>


#define UPPER_TRIANGULAR 1
/*-------------------------------------------------------------------
 * Function:  itmv_mult
 * Purpose:   Run t iterations of parallel computation:  {y=d+Ax; x=y}.  The matrix is distributed
 *            by block rows and the column vectors d, x, yare distributed by blocks
 * In args:   local_A:  calling process' rows of matrix A
 *            local_d:  calling process' components of vector d
 *            global_x:  Store the final vector x  in process 0 when returning
 *            matrix_type:  matrix_type=0 means A is a regular matrix. 
 *            		    matrix_type=1 (UPPER_TRIANGULAR) means A is an upper triangular matrix
 *            n:        the global  number of columns (same as the number of rows)
 *            t: 	the number of iterations
 *            blocksize:  size of local array for x, which should be n/no_proc
 *            my_rank:        local process ID
 *            no_proc:        no of processes
 *            comm:     communicator containing all calling processes
 * In/out:    local_x:  calling process' components of vector x
 *            local_y:  calling process' components of vector y
 * Return:  1  means succesful
 * 	    0  means unsuccessful 
 * Errors:   If an error is detected (e.g. n is non-positive, n is not evenly
 *           divisible by the number of processes, malloc fails), the program returns 0.
 * Global:    This function should NOT access any global variable.
 */
int itmv_mult(
      double    local_A[]  /* in  */, 
      double    local_x[]  /* in  */, 
      double    local_d[]  /* in  */, 
      double    local_y[]  /* out */,
      double    global_x[] /* out */,
      int       matrix_type /* in  */, 
      int       n          /* in  */,
      int       t          /* in  */,
      int       blocksize  /* in  */, 
      int       my_rank    /* in  */,
      int       no_proc    /* in  */,
      MPI_Comm  comm       /* in  */) 
{
   double* x;
   int local_i, j, start, k;
   int succ, all_succ;

   if (n<=0 || blocksize<=0 ||local_A==NULL || local_x==NULL || local_y==NULL ||no_proc<=0|| my_rank<0 |my_rank>=no_proc)
	   return 0;
   if( n % no_proc!=0) /* n is not divisible by no_proc */
	   return 0;
   if( n/no_proc!= blocksize) /* wrong local array size */
	   return 0;

   /*Your solution */
   x=malloc(n*sizeof(double));; //declare our x. Wait what why tho (?) 
   //this allgather uses local_x and gives a complete vec x to every processor to use
   MPI_Allgather(local_x, blocksize, MPI_DOUBLE, x, blocksize, MPI_DOUBLE, comm);

   //printf("in processor: %d. blocksize is %d, and n is %d\n", my_rank, blocksize, n);
   
   for (k=0; k<t; k++)
   {
      for (local_i=0; local_i<n; local_i++)
         {
            local_y[local_i]=local_d[local_i]; //y[i]+=d[i] portion
            //the triangle matrix handling stuff
            if(matrix_type==UPPER_TRIANGULAR){
               start=local_i;
            }else {
               start=0;
            } 

            for (int j=start; j<n; j++)
            {
               local_y[local_i]+=local_A[local_i*n+j]*x[j]; //y[i]= A*x[j] part
               printf("in processor: %d. local y is %d at locali: %i \n", my_rank, local_y[local_i], local_i);
            }
            
         }

         //x= y part, for each one 
         for (local_i = 0; local_i < blocksize; local_i++) {
               local_x[local_i]= local_y[local_i];
         }

   }
  
   //putting everything back to global_x in processor 0??? 
   if (my_rank==0)
   {
      for (int i= 0; i < n; i++) {
      		global_x[i]= local_x[i];
	   }
   }
   //MPI_Gather(local_x,blocksize,MPI_DOUBLE, global_x, blocksize, MPI_DOUBLE,0,comm);
   free(x);

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
 * Return:  1  means succesful
 * 	    0  means unsuccessful 
 * Errors:   If an error is detected (e.g. n is non-positive, matrix/vector pointers are NULL. 
 *           
 */
int itmv_mult_seq( double A[],  double x[], double d[], double  y[], 
		int  matrix_type, int n, int t) {
   int i, j, start, k;

   if(n<=0 || A==NULL || x==NULL ||   d==NULL|| y==NULL)
	return 0;

   for(k=0; k<t; k++){
   	for (i = 0; i < n; i++) {
      	y[i]= d[i];
      	if(matrix_type==UPPER_TRIANGULAR){
            start=i;
         }else {
			  start=0;
      	}
      	for (j = start; j < n; j++) {
         	y[i] += A[i*n+j]*x[j];
		   }
   	}
   	for (i = 0; i < n; i++) {
      		x[i]= y[i];
	}
   }
   return 1;
}
