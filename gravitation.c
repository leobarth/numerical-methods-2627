#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 1000
#define STEPS 200
#define G 6.67430e-11
#define DT 1000.0

typedef struct {
    double x, y, z;
    double vx, vy, vz;
    double mass;
} Particle;

double random_double(double min, double max)
{
    return min + (max - min) * ((double) rand() / RAND_MAX);
}

int main(void)
{
    Particle *p = malloc(N * sizeof(Particle));

    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    srand(42);

    /* Initialize particles */
    for (int i = 0; i < N; i++) {
        p[i].x = random_double(-1e11, 1e11);
        p[i].y = random_double(-1e11, 1e11);
        p[i].z = random_double(-1e11, 1e11);

        p[i].vx = random_double(-1e3, 1e3);
        p[i].vy = random_double(-1e3, 1e3);
        p[i].vz = random_double(-1e3, 1e3);

        p[i].mass = random_double(1e20, 1e25);
    }

    clock_t start = clock();

    for (int step = 0; step < STEPS; step++) {

        /* Calculate gravitational acceleration */
        for (int i = 0; i < N; i++) {

            double ax = 0.0;
            double ay = 0.0;
            double az = 0.0;

            for (int j = 0; j < N; j++) {

                if (i == j)
                    continue;

                double dx = p[j].x - p[i].x;
                double dy = p[j].y - p[i].y;
                double dz = p[j].z - p[i].z;

                double distance_squared =
                    dx * dx +
                    dy * dy +
                    dz * dz;

                /*
                 * Softening prevents singularities when
                 * particles get extremely close.
                 */
                double distance =
                    sqrt(distance_squared + 1e16);

                double factor =
                    G * p[j].mass /
                    (distance * distance * distance);

                ax += factor * dx;
                ay += factor * dy;
                az += factor * dz;
            }

            /* Update velocity */
            p[i].vx += ax * DT;
            p[i].vy += ay * DT;
            p[i].vz += az * DT;
        }

        /* Update position */
        for (int i = 0; i < N; i++) {
            p[i].x += p[i].vx * DT;
            p[i].y += p[i].vy * DT;
            p[i].z += p[i].vz * DT;
        }

        if (step % 100 == 0) {
            printf("Step %d / %d\n", step, STEPS);
        }
    }

    clock_t end = clock();

    double elapsed =
        (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nSimulation finished.\n");
    printf("Time: %.3f seconds\n", elapsed);

    /*
     * Print some values so that the compiler cannot
     * trivially eliminate the computation.
     */
    double checksum = 0.0;

    for (int i = 0; i < N; i++) {
        checksum += p[i].x;
        checksum += p[i].y;
        checksum += p[i].z;
    }

    printf("Checksum: %.10e\n", checksum);

    free(p);

    return 0;
}