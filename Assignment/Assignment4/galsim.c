#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
// using define instead of variable
#define EPSILON 0.001

// #pragma region Particle
/* Structure to store the state of a particle
 * x: position x
 * y: position y
 * mass: mass of the particle
 * v_x: velocity x
 * v_y: velocity y
 * brightness: brightness of the particle
 */
typedef struct 
{
    double* x;
    double* y;
    double* mass;
    double* v_x;
    double* v_y;
    double* brightness;
} Particle;



/* read 6 input arguments from the command line 
 * N: the number of stars/particles to simulate
 * filename: the filename of the file to read the initial configuration from
 * nsteps: the number of timesteps
 * delta_t: the timestep ∆t
 * graphics: 1 or 0 meaning graphics on/of
 * n_threads: number od threads
 */
int main(int argc, char *argv[])
{

// #pragma region ParseArguments
    // check if the number of arguments is correct 
    if (argc != 7) {
        printf("Usage: %s N filename nsteps delta_t graphics\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    char *filename = argv[2];
    int nsteps = atoi(argv[3]);
    double delta_t = atof(argv[4]);
    bool graphics = atoi(argv[5]);
    int n_threads = atoi(argv[6]);
// #pragma endregion

// #pragma region ReadFile
    FILE *file = fopen(filename, "rb");
    if (file == NULL) 
    {
        printf("Error: cannot open file %s\n", filename);
        return 1;
    }

    Particle particles;

    // malloc for particles
    particles.x = (double*)malloc(sizeof(double) * N);
    particles.y = (double*)malloc(sizeof(double) * N);
    particles.mass = (double*)malloc(sizeof(double) * N);
    particles.v_x = (double*)malloc(sizeof(double) * N);
    particles.v_y = (double*)malloc(sizeof(double) * N);
    particles.brightness = (double*)malloc(sizeof(double) * N);


    for(int i = 0; i < N; ++i)
    {
        double data[6];
        size_t read_count = fread(data, sizeof(double), 6, file);
        // printf("Read: %lf %lf %lf %lf %lf %lf\n", data[0], data[1], data[2], data[3], data[4], data[5]);
        // particles[i] = Create(data[0], data[1], data[2], data[3], data[4], data[5]);
        particles.x[i] = data[0];
        particles.y[i] = data[1];
        particles.mass[i] = data[2];
        particles.v_x[i] = data[3];
        particles.v_y[i] = data[4];
        particles.brightness[i] = data[5];
        // Print(particles[i]);
    }
    fclose(file);
// #pragma endregion

// #pragma region Simulation
    double G = 100.0 / N;
    // Allocate force arrays outside the time step loop
    double *F_x = (double*)malloc(sizeof(double) * N);
    double *F_y = (double*)malloc(sizeof(double) * N);
    for (int t = 0; t < nsteps; ++t)
    {
        // Initialize force arrays to zero at the start of each time step
        memset(F_x, 0, sizeof(double) * N);
        memset(F_y, 0, sizeof(double) * N);

        for (int i = 0; i < N; ++i)
        {
            /* calculate the force exerted on particle i by other N-1 particles */ 
            
            // double F_i = F(N, particles, i, G);
            // 
            /* F_i = -G * m_i * Σ m_j / (r_ij+epsilon)^3 * r_ij^
             * epsilon = 10^-3
             */
            double F_i = 0.0;
            double F_j = 0.0;
            for (int j = i+1; j < N; ++j) 
            {
                // reduce the redundant calculations of "particles[i]->x - particles[j]->x" and "particles[i]->y - particles[j]->y"
                double dx = particles.x[i] - particles.x[j];
                double dy = particles.y[i] - particles.y[j];

                /* r_ij: the distance between particle i and j
                * r_ij^2 = (x_i − x_j)^2 + (y_i − y_j)^2
                *reduce the redundant calculations of r + EPSILON
                */
                double r = sqrt((dx * dx) + (dy * dy)) + EPSILON;
                double inv_r3 = 1.0 / (r * r * r);

                // instead of using pow
                double f_i = particles.mass[j] * inv_r3;
                double f_j = particles.mass[i] * inv_r3;

                F_i += f_i * dx;
                F_j += f_i * dy;
                F_x[j] -= f_j * dx;
                F_y[j] -= f_j * dy;
            }
            F_x[i] += F_i;
            F_y[i] += F_j;
            particles.v_x[i] += - G * F_x[i] * delta_t;
            particles.v_y[i] += - G * F_y[i] * delta_t;
            particles.x[i] += particles.v_x[i] * delta_t;
            particles.y[i] += particles.v_y[i] * delta_t;
        }
    }

    // Free allocated memory for force arrays
    free(F_x);
    free(F_y);
// #pragma endregion
// #pragma region WriteFile
    // output result.gal as binary file format
    FILE *output = fopen("result.gal", "wb");
    if (output == NULL) 
    {
        printf("Error: cannot open file result.gal\n");
        return 1;
    }

    for (int i = 0; i < N; ++i)
    {
        fwrite(&particles.x[i], sizeof(double), 1, output);
        fwrite(&particles.y[i], sizeof(double), 1, output);
        fwrite(&particles.mass[i], sizeof(double), 1, output);
        fwrite(&particles.v_x[i], sizeof(double), 1, output);
        fwrite(&particles.v_y[i], sizeof(double), 1, output);
        fwrite(&particles.brightness[i], sizeof(double), 1, output);
    }

    fclose(output);

// #pragma endregion

// #pragma region FreeMemory
    
    free(particles.x);
    free(particles.y);
    free(particles.mass);
    free(particles.v_x);
    free(particles.v_y);
    free(particles.brightness);
// #pragma endregion

    return 0;
}
