#!/bin/bash
#SBATCH --job-name="itmv_mult_seq"
#SBATCH --output="job_itmv_mult_seq.%j.out"
#SBATCH --partition=compute
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --export=ALL
#SBATCH -t 00:01:00

./itmv_mult_seq
