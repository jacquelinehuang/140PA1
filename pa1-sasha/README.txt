Last name of Student 1: Romanova
First name of Student 1: Sasha
Email of Student 1: 
Last name of Student 2: Huang
First name of Student 2: Jacqueline
Email of Student 2: jacquelinehuang@ucsb.edu



Report for Question 1
performance summarywhen the number of tosses =1,000,000,000. 
Examine the parallel time, speedup, and efficiency with 4 and 8 MPI nodes.

Sequential: Program pi_seq.c: wall clock time = 16.896042 seconds
4 Cores:
parallel time:
	Test 3: Wall clock time = 5.560116 at Proc 0 of 4 processes
speedup:
	speedup = Tserial/Tparallel = 16.890642/5.560116
	=3.03782187278
efficiency:
	E= speedup/n = 3.03782187278/4
	= 0.75945546819

8 Cores:
parallel time:
	Test 3: Wall clock time = 2.775991 at Proc 0 of 8 processes
speedup:
	speedup = Tserial/Tparallel = 16.890642/2.775991
	=6.08454494269
efficiency:
	E= speedup/n = 6.08454494269/8
	=0.76056811783

---------------------------------
Report for Question 3.a 
Performance report when n=4096and t=1024for the above test case.  Report the parallel time, speedup, and efficiency when the number of cores used is 2 and 4 where each core runs one MPI process.

Sequential Time:
Program diagonal itmv seq.c: wall clock time = 12.012097 seconds
Program triangular time seq.c: wall clock time = 6.123364 seconds

2 Cores
parallel time:
speedup:
    Speedup = Tserial/Tparallel
    =
efficiency:
E=Speedup/n = (Tserial/Tparallel)/n
4 Cores:
parallel time:
speedup:
    Speedup = Tserial/Tparallel
efficiency:
    E=Speedup/n = (Tserial/Tparallel)/n
    
----------------------
Report for Question 3.b
Performance summary when n=4096 and t=1024 for the above test case.  Report the parallel time, speedup, and efficiency  when the number of cores usedis 2 and4 where each core runs one MPI process. 


 2 Cores
Parallel time
 2 Cores Wall clock time = 
speedup:
    Speedup = Tserial/Tparallel
efficiency:
    E=Speedup/n = (Tserial/Tparallel)/n

4 Cores:
parallel time:
    4 Cores Wall clock time = 
speedup:
    Speedup = Tserial/Tparallel
efficiency:
    E=Speedup/n = (Tserial/Tparallel)/n

The efficiency for 3b is worse than for 3a since the data distribution is unequal for each processor. Processors that have less data enties will idle, causing the recorded parallel time to go up. We can fix this by finding a different way to distribute data across each processor. 
