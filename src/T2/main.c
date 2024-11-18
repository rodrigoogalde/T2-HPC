#include <stdio.h>
#include <stdlib.h>

#define SIZE 3000
#define STEPS 10000

int main() {
    double *grid = malloc(SIZE * SIZE * sizeof(double));
    if (grid == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for grid.\n");
        return EXIT_FAILURE;
    }

    int i, j, step;

    for (i = 0; i < SIZE * SIZE; i++) {
        grid[i] = 0.0;
    }

    grid[(SIZE / 2) * SIZE + (SIZE / 2)] = 10000.0;

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

    printf("Final grid center value: %f\n", grid[(SIZE / 2) * SIZE + (SIZE / 2)]);

    free(grid);

    return 0;
}
