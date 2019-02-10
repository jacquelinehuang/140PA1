
/*
 * File:     treesum_mpi.c
 *
 * Purpose:  Use tree-structured communication to find the global sum
 *           of a random collection of ints.  This version doesn't
 *           require that comm_sz be a power of 2.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>




/*-------------------------------------------------------------------
 * Function:   global_sum
 * Purpose:    Implement a global sum using tree-structured communication
 * Notes:       
 * 1.  The return value for global sum is only valid on process 0
 */
int
global_sum (int my_int /* in */ ,
            int my_rank /* in */ ,
            int comm_sz /* in */ ,
            MPI_Comm comm /* in */ )
{

	int divisor = 2;
	int diff = 1;
	double my_sum = my_int;
	int partner;
	double received_val; 

	while(divisor <= comm_sz) {
		if(my_rank % divisor == 0) {
			partner = my_rank + diff;
			// receive value from partner core
			MPI_Recv(&received_val, 1, MPI_DOUBLE, partner, 0, comm, MPI_STATUS_IGNORE);
			my_sum += received_val;
		} else if((my_rank % (divisor/2)) == 0) {
			partner = my_rank - diff;
			// send sum to partner core
			MPI_Send(&my_sum, 1, MPI_DOUBLE, partner, 0, comm);
		}
		divisor *= 2;
		diff *= 2;
	}

	if(my_rank == 0) {
		return my_sum;
	}
	return 0;
}                               /* Global_sum */
