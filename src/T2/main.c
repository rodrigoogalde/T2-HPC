#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 3000 // Dimensión cuadricula
#define STEPS 10000 // Cantidad de iteraciones

int main() {
    double *grid = malloc(SIZE * SIZE * sizeof(double)); // Arreglo unidemensional de tamaño SIZE * SIZE
    if (grid == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for grid.\n");
        return EXIT_FAILURE;
    }

    int i, j, step;

    #pragma omp parallel for
    for (i = 0; i < SIZE * SIZE; i++) {
        grid[i] = 0.0; // Inicializa el arreglo con 0
    }

    grid[(SIZE / 2) * SIZE + (SIZE / 2)] = 10000.0; // Asigna un valor inicial al centro de la cuadricula

    // Itera STEPS veces
    // Para cada celda de la cuadricula, calcula el promedio de los valores de las celdas vecinas, eso sin contar
    // las celdas en los bordes. Se esta simulando el proceso de difusión de calor en una placa.

    #pragma omp parallel for collapse(2) private(i, j) //shared(grid, SIZE)
    for (step = 0; step < STEPS; step++) { 
        for (i = 1; i < SIZE - 1; i++) {
            for (j = 1; j < SIZE - 1; j++) {
                grid[i * SIZE + j] = 0.25 * (
                    grid[(i - 1) * SIZE + j] + 
                    grid[(i + 1) * SIZE + j] + 
                    grid[i * SIZE + (j - 1)] + 
                    grid[i * SIZE + (j + 1)]
                );
            }
        }
    }

    // Se imprime cuanto calor queda en el centro de la cuadricula
    printf("Final grid center value: %f\n", grid[(SIZE / 2) * SIZE + (SIZE / 2)]);

    free(grid);

    return 0;
}