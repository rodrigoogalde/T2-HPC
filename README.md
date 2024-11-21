# T2-HPC

## Resumen resultados

Al ejecutar el secuencial en local se demora ./T2_secuencial  493.65s user 2.92s system 99% cpu 8:21.25 total

Al ejecutar el secuencial en el cluster 

**real**	**9m10.072s**

**user**	**9m10.016s**

**sys**	**0m0.036s**

Al ejecutar el paralelo en local ./main  684.32s user 4.03s system 728% cpu 1:34.55 total

Al ejecutar el paralelo en el cluster 

**real**	**1m54.533s**

**user**	**11m53.723s**

**sys**	**0m0.492s**

### Connect to the Cluster

```
ssh antonia-blanco@kraken.ing.puc.cl
```

```shell
ssh rjogalde@kraken.ing.puc.cl
```

### Utils Commands

```shell
# Copy from cluster to local
scp rjogalde@kraken.ing.puc.cl:~/src

# Copy from local to cluster
scp ./src/Secuencial/main.c rjogalde@kraken.ing.puc.cl:~/main.c
scp run.sh rjogalde@kraken.ing.puc.cl:~/run.sh
```

## Cluster

###### Para ver las tareas

```
squeue
```

```
squeue -o "%.10u %.10i %.10P %.20j %.11M %.10T %.4C %N" -S -t
```

###### Enviar un trabajo

```
sbatch nombre_del_script.sh
```

###### Ver el estado de los nodos

```
sisinfo
```

```
sinfo -N -o "%.10N %.10O %.10e %.20C"
```

###### Eliminar un trabajo

```
scancel 23
```

###### Salir del cluster

```
exit
```

###### Ver mis trabajos en cola

`squeue -u $USER`

```
squeue -u antonia-blanco
```

###### Detalles de un trabajo

```
scontrol show job xxxx
```

###### Borrar todos los archivos de extención txt

```
rm *.txt
```

## Variables de Ambiente

Primero se debe crear la variable de ambiente

**export OMP_NUM_THREADS=6**

y después se debe volver a compilar antes de ejecutar

**antonia-blanco@kraken:~$ gcc -fopenmp omp_hello.c -o omp_helloo**

Otra opción es cambiarlo dentro del código con

**omp_set_num_threads(10);**

por última opción es en la directiva misma **#pragma omp parallel private(nthreads, tid) num_threads(13)**

## Subir archivos

Es desde mi computador

Copiar desde el servidor a mi computador

```
scp antonia-blanco@kraken.ing.puc.cl:~/archivo.txt ./ruta_donde_copiar/nombre_a_copiar.txt
```

Subir desde mi computador al servidor

scp archivo.txt antonia-blanco@kraken.ing.puc.cl:~/nombre_a_copiar.txt

## **Local**

`gcc-14 -fopenmp paralelisado.c -o paralelisado` Compilar un programa en c que utiliza OpenMp, en mi computador

`time ./paralelisado` Ejecutar y visualizar tiempo de un programa en c
