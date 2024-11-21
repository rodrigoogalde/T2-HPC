#!/bin/bash
#SBATCH --job-name=sum_numbers
#SBATCH --output=sum_numbers.out
#SBATCH --error=sum_numbers.err
#SBATCH --ntasks=8
#SBATCH --cpus-per-task=8
#SBATCH --time=00:30:00
#SBATCH --partition=all

echo "start script"
date

module load gcc

echo "Compilando el programa..."
gcc -fopenmp -o main main.c

export OMP_NUM_THREADS=8

echo "Ejecutando el programa..."
{ time ./main; } 2>> time.txt

echo "Fin del script"
date
