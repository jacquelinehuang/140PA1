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
int global_sum(
      int my_int    /* in */,
      int my_rank   /* in */,
      int comm_sz   /* in */,
      MPI_Comm comm /* in */) {
   
   int my_sum = my_int;
   if( (my_rank %2 !=0 &&me>0) //if im not even and not 0, send my sum to the left
   Send (my_sum, my_rank -1);

   //recieving and stuff 

   /* Your solution*/
/*
   pseudofrom hw
   me=mynode();
   p= noproc();
   sum=x[me];
   if( (me %2 !=0 &&me>0) //if im not even and not 0, send left
      Send (sum, me -1);
   For( gap=1; gap<p; gap =gap*2)
   {
      if(me%(2*gap) ==0)) //if im divisible by 2*gap
      {
         Receive(other_sum, me+gap); //recieve sums from processor at me+gap'
         //this breaks down here trying p=6 core=4 at gap2
         sum= other_sum+sum;

         if( (me % (4*gap)) !=0 && me>=2*gap) //if me not divisible by 4g and > 2*g
            Send (sum, me -2*gap); //send sum to 2*gap positions left 

      }
   }
*/

   return my_sum;
}  /* Global_sum */
