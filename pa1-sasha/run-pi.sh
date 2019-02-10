#!/bin/bash
#SBATCH --job-name="seqpi"
#SBATCH --output="job_seqpi.%j.out"
#SBATCH --partition=compute
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --export=ALL
#SBATCH -t 00:01:00

./pi 1000000000.
