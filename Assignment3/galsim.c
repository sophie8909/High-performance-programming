#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#define EPSILON 0.001

#pragma region Particle
/* Structure to store the state of a particle
 * x: position x
 * y: position y
 * mass: mass of the particle
 * v_x: velocity x
 * v_y: velocity y
 * brightness: brightness of the particle
 * e_x: unit vector in x direction
 * e_y: unit vector in y direction
 */
typedef struct 
{
    double x, y, mass, v_x, v_y, brightness;
    double e_x, e_y;
} Particle;


Particle* Create(double x, double y, double mass, double v_x, double v_y, double brightness) 
{
    Particle* p = (Particle*)malloc(sizeof(Particle));
    p->x = x;
    p->y = y;
    p->mass = mass;
    p->v_x = v_x;
    p->v_y = v_y;
    p->brightness = brightness;
    p->e_x = 0.0;
    p->e_y = 0.0;
    return p;
}

void Destroy(Particle* p) 
{
    free(p);
}

// print to terminal
void Print(Particle* p) 
{
    printf("%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n", p->x, p->y, p->mass, p->v_x, p->v_y, p->brightness);
}

// write to binary file
void Write(FILE *file, Particle* p)
{
    fwrite(&p->x, sizeof(double), 1, file);
    fwrite(&p->y, sizeof(double), 1, file);
    fwrite(&p->mass, sizeof(double), 1, file);
    fwrite(&p->v_x, sizeof(double), 1, file);
    fwrite(&p->v_y, sizeof(double), 1, file);
    fwrite(&p->brightness, sizeof(double), 1, file);

}
# pragma endregion

#pragma region Movation
/* Calculate the force exerted on particle i by other N-1 particles
 * N: number of particles
 * particles: array of pointers to particles
 * i: index of the particle
 * G: gravitational constant
 */ 
double F(int N, Particle** particles, int i, double G) 
{
    /* F_i = -G * m_i * Σ m_j / (r_ij+epsilon)^3 * r_ij^
     * epsilon = 10^-3
    */
    double F = 0.0;
    for (int j = 0; j < N; j++) 
    {
        if (i != j) 
        {
            double dx = particles[i]->x - particles[j]->x;
            double dy = particles[i]->y - particles[j]->y;
            /* r_ij: the vector pointing from particle j to particle i
             * r_ij = (x_i − x_j)e_x + (y_i − y_j)e_y
             */ 
            double r = dx * particles[j]->e_x + dy * particles[j]->e_y;
            /* gamma_ij: the distance between particle i and j
             * gamma_ij^2 = (x_i − x_j)^2 + (y_i − y_j)^2
             */
            double gamma = sqrt((dx * dx) + (dy * dy));
            // r_ij^ = r_ij / gamma_ij
            double gamma_epsilln = gamma + EPSILON;


            F += particles[j]->mass  * r / (gamma_epsilln * gamma_epsilln * gamma_epsilln);
        }
    }
    return -G * particles[i]->mass * F;

}

#pragma endregion


/* read 5 input arguments from the command line 
 * N: the number of stars/particles to simulate
 * filename: the filename of the file to read the initial configuration from
 * nsteps: the number of timesteps
 * delta_t: the timestep ∆t
 * graphics: 1 or 0 meaning graphics on/of
 */
int main(int argc, char *argv[])
{
    // check if the number of arguments is correct 
    if (argc != 6) {
        printf("Usage: %s N filename nsteps delta_t graphics\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    char *filename = argv[2];
    int nsteps = atoi(argv[3]);
    double delta_t = atof(argv[4]);
    bool graphics = atoi(argv[5]);

#pragma region ReadFile
    FILE *file = fopen(filename, "rb");
    if (file == NULL) 
    {
        printf("Error: cannot open file %s\n", filename);
        return 1;
    }

    Particle** particles = (Particle**)malloc(N * sizeof(Particle*));
    for (int i = 0; i < N; i++) 
    {
        double data[6];
        size_t read_count = fread(data, sizeof(double), 6, file);
        // printf("Read: %lf %lf %lf %lf %lf %lf\n", data[0], data[1], data[2], data[3], data[4], data[5]);
        particles[i] = Create(data[0], data[1], data[2], data[3], data[4], data[5]);
        // Print(particles[i]);
    }

    fclose(file);
#pragma endregion

    // L x W dimensionless domain
    double L = 1.0, W = 1.0;
    double G = 100.0 / N;
    for (int t = 0; t < nsteps; ++t)
    {
        // update the position of each particle
        for (int i = 0; i < N; i++) 
        {
            // calculate the force exerted on particle i by other N-1 particles
            double F_i = F(N, particles, i, G);
            /* update the position of particle i
             * a_i^n = F_i^n / m_i
             * u_i^n+1 = u_i^n + a_i^n * delta_t
             * x_i^n+1 = x_i^n + u_i^n+1 * delta_t
             */ 
            double a_x = F_i / particles[i]->mass;
            particles[i]->v_x += a_x * delta_t;
            particles[i]->x += particles[i]->v_x * delta_t;

            double a_y = F_i / particles[i]->mass;
            particles[i]->v_y += a_y * delta_t;
            particles[i]->y += particles[i]->v_y * delta_t;
        }
    }

    // output result.gal as binary file format
    FILE *output = fopen("result.gal", "wb");
    if (output == NULL) 
    {
        printf("Error: cannot open file result.gal\n");
        return 1;
    }
    for(int i = 0; i < N; ++i)
        Write(output, particles[i]);

    fclose(output);


#pragma region FreeMemory
    for (int i = 0; i < N; i++) 
    {
        Destroy(particles[i]);
    }
    free(particles);
#pragma endregion

    return 0;
}
