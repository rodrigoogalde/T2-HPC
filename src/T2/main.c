#include <stdio.h>
#include <stdlib.h>

#define SIZE 3000
#define STEPS 10000

int main() {
    double *grid_current = malloc(SIZE * SIZE * sizeof(double));
    double *grid_next = malloc(SIZE * SIZE * sizeof(double));
    if (grid_current == NULL || grid_next == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for grids.\n");
        return EXIT_FAILURE;
    }

    int i, j, step;
    int center = (SIZE / 2) * SIZE + (SIZE / 2);

    // Inicializar las matrices
    #pragma omp parallel for private(i, j) collapse(2)
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            grid_current[i * SIZE + j] = 0.0;
            grid_next[i * SIZE + j] = 0.0;
        }
    }

    // Establecer la fuente de calor en el centro
    grid_current[center] = 10000.0;
    grid_next[center] = 10000.0;

    for (step = 0; step < STEPS; step++) {
        #pragma omp parallel for private(i, j)
        for (i = 1; i < SIZE - 1; i++) {
            for (j = 1; j < SIZE - 1; j++) {
                if (i * SIZE + j == center) continue; // Mantener la fuente de calor constante
                grid_next[i * SIZE + j] = 0.25 * (
                    grid_current[(i - 1) * SIZE + j] +
                    grid_current[(i + 1) * SIZE + j] +
                    grid_current[i * SIZE + (j - 1)] +
                    grid_current[i * SIZE + (j + 1)]
                );
            }
        }
        // Intercambiar las matrices
        double *temp = grid_current;
        grid_current = grid_next;
        grid_next = temp;
    }

    printf("Final grid center value: %f\n", grid_current[center]);

    free(grid_current);
    free(grid_next);

    return 0;
}

