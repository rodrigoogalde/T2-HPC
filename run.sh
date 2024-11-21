#!/bin/bash
#SBATCH --job-name=t2
#SBATCH --output=t2.out
#SBATCH --error=t2.err
#SBATCH --ntasks=8
#SBATCH --cpus-per-task=8
#SBATCH --time=01:30:00
#SBATCH --partition=all

echo "Inicio del script: $(date)" > time.txt
date

module load gcc

echo "Compilando el programa..."
gcc -fopenmp -o main main.c

for threads in {1..50}
do
    export OMP_NUM_THREADS=$threads

    { time ./main; } 2>> time.txt
    echo -n "Fue ejecutado con $OMP_NUM_THREADS hilos... " >> time.txt
    echo  "" >> time.txt
    echo  "" >> time.txt
done
