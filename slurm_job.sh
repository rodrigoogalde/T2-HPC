#!/bin/bash
#SBATCH --job-name=t2
#SBATCH --output=t2.out
#SBATCH --error=t2.err
#SBATCH --ntasks=8
#SBATCH --cpus-per-task=8
#SBATCH --time=01:30:00
#SBATCH --partition=all

echo 'Inicio del script: Thu Nov 21 13:04:39 -03 2024' > time.txt
date

module load gcc

echo 'Compilando el programa...'
gcc -std=gnu11 -fopenmp -O3 -o main src/main.c

for threads in {10..11}
do
    export OMP_NUM_THREADS=$threads
    { time ./main; } 2>> time.txt
    echo -n 'Fue ejecutado con $OMP_NUM_THREADS hilos... ' >> time.txt
    echo '' >> time.txt
    echo '' >> time.txt
done

echo 'Termino del script: Thu Nov 21 13:04:39 -03 2024' >> time.txt
