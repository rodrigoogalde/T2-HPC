#!/bin/bash
#SBATCH --job-name=sum_numbers
#SBATCH --output=sum_numbers.out
#SBATCH --error=sum_numbers.err
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=8
#SBATCH --time=00:30:00

module load gcc

gcc -fopenmp -o main main.c
export OMP_NUM_THREADS=8
time ./main
