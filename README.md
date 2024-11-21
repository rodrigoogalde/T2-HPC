# T2-HPC

### Connect to the Cluster
```shell
ssh rjogalde@kraken.ing.puc.cl
```

### Utils Commands
```shell

sbatch run.sh


# Copy from cluster to local
scp rjogalde@kraken.ing.puc.cl:~/src

scp rjogalde@kraken.ing.puc.cl:~/t2.err ./t2.err
scp rjogalde@kraken.ing.puc.cl:~/t2.out ./t2.out
scp rjogalde@kraken.ing.puc.cl:~/time.txt ./time.txt

# Copy from local to cluster
scp ./src/T2/main.c rjogalde@kraken.ing.puc.cl:~/main.c
scp run.sh rjogalde@kraken.ing.puc.cl:~/run.sh

squeue
squeue -u rjogalde
```

Final grid center value: 0.159151