# Assignment 3

Ting-Hsuan Lien

## Problem

Calculate the evolution of *N* particles in a gravitational simulation. 

## Solution

### Data structure (for particle)

Simply record all information of particle

```c
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
    double x, y, mass, v_x, v_y, brightness;
} Particle;
```

### Structure (code)

My code can spilt into 6 main part. 

Particle:  Contains the definition of the `Particle` structure and function `Print()` for debugging purposes.

ParseArguments: reading input data from files to initialize particle properties.

ReadFile: read input data and create particles.

Simulation: The core of the program where all computations occur.

WriteFile: writing final result in to result.gal

FreeMemory: release all memory in the end.

### Algorithm

Algorithm implement in Simulation part. Following are pseudocode.

```c
for t in nsteps:
    for i in N:
        F = 0.0;
        for j in N:
			if i != j:
				dx = particles[i]->x - particles[j]->x;
				dy = particles[i]->y - particles[j]->y;
				r = sqrt((dx * dx) + (dy * dy));
                F += particles[j]->mass / (r * r * r);
		F *= -G * particles[i]->mass;
		a = F / particles[i]->mass;
        update paricles[i] velocity
    for i in N:
        update paricles[i] position

```

## Performance and Discussion

All experiments run same data in 200 step (which has ref_output).

#### Original Version (without any optimizations)

| input data      | real     | user     | sys      |
| --------------- | -------- | -------- | -------- |
| ellipse_N_00010 | 0m0.008s | 0m0.002s | 0m0.000s |
| ellipse_N_00100 | 0m0.027s | 0m0.020s | 0m0.000s |
| ellipse_N_00500 | 0m0.485s | 0m0.456s | 0m0.000s |
| ellipse_N_01000 | 0m1.890s | 0m1.798s | 0m0.000s |
| ellipse_N_02000 | 0m6.200s | 0m7.277s | 0m0.000s |

In the **Original Version**, no specific optimizations were applied. The graph below clearly shows an **O(n²)** curve.

![original](C:\Users\Sophie\Desktop\High-performance-programming\Assignment3\report\original.png)

Figure 1: original version - real time performance

#### Compile with `-o3`

| input data      | real     | user     | sys      |
| --------------- | -------- | -------- | -------- |
| ellipse_N_00010 | 0m0.008s | 0m0.001s | 0m0.000s |
| ellipse_N_00100 | 0m0.015s | 0m0.008s | 0m0.000s |
| ellipse_N_00500 | 0m0.179s | 0m0.163s | 0m0.000s |
| ellipse_N_01000 | 0m0.681s | 0m0.642s | 0m0.000s |
| ellipse_N_02000 | 0m1.261s | 0m2.587s | 0m0.000s |

In this version, no modifications were made to the code; only the `-O3` optimization flag was used during compilation. The execution time was significantly reduced. In the largest test case, the **real time** decreased by **79.6%**.

In Figure 2 the time complexity seem not like **O(n²)**, but no modification of code, the algorithm still **O(n²)**.

![o3](C:\Users\Sophie\Desktop\High-performance-programming\Assignment3\report\o3.png)

Figure 2: Compile with `-o3` version - real time performance

#### Compile with `-funroll-loops`
| input data      | real     | user     | sys      |
| --------------- | -------- | -------- | -------- |
| ellipse_N_00010 | 0m0.009s | 0m0.002s | 0m0.000s |
| ellipse_N_00100 | 0m0.016s | 0m0.008s | 0m0.000s |
| ellipse_N_00500 | 0m0.180s | 0m0.164s | 0m0.000s |
| ellipse_N_01000 | 0m0.688s | 0m0.648s | 0m0.000s |
| ellipse_N_02000 | 0m1.271s | 0m2.602s | 0m0.001s |

#### Move `F()` into main
| input data      | real     | user     | sys      |
| --------------- | -------- | -------- | -------- |
| ellipse_N_00010 | 0m0.008s | 0m0.002s | 0m0.000s |
| ellipse_N_00100 | 0m0.015s | 0m0.008s | 0m0.000s |
| ellipse_N_00500 | 0m0.177s | 0m0.152s | 0m0.009s |
| ellipse_N_01000 | 0m0.671s | 0m0.631s | 0m0.000s |
| ellipse_N_02000 | 0m1.169s | 0m2.516s | 0m0.010s |

#### Remove if ( i != j ) in loop
| input data      | real     | user     | sys      |
| --------------- | -------- | -------- | -------- |
| ellipse_N_00010 | 0m0.008s | 0m0.001s | 0m0.000s |
| ellipse_N_00100 | 0m0.011s | 0m0.005s | 0m0.000s |
| ellipse_N_00500 | 0m0.103s | 0m0.090s | 0m0.000s |
| ellipse_N_01000 | 0m0.377s | 0m0.342s | 0m0.009s |
| ellipse_N_02000 | 0m1.487s | 0m1.406s | 0m0.000s |

#### Change for to do-while
| input data      | real     | user     | sys      |
| --------------- | -------- | -------- | -------- |
| ellipse_N_00010 | 0m0.008s | 0m0.001s | 0m0.000s |
| ellipse_N_00100 | 0m0.012s | 0m0.005s | 0m0.000s |
| ellipse_N_00500 | 0m0.102s | 0m0.090s | 0m0.000s |
| ellipse_N_01000 | 0m0.383s | 0m0.357s | 0m0.000s |
| ellipse_N_02000 | 0m1.499s | 0m1.408s | 0m0.010s |

#### Move `Destroy()` into main

| input data      | real     | user     | sys      |
| --------------- | -------- | -------- | -------- |
| ellipse_N_00010 | 0m0.008s | 0m0.001s | 0m0.000s |
| ellipse_N_00100 | 0m0.011s | 0m0.005s | 0m0.000s |
| ellipse_N_00500 | 0m0.098s | 0m0.086s | 0m0.000s |
| ellipse_N_01000 | 0m0.363s | 0m0.336s | 0m0.000s |
| ellipse_N_02000 | 0m1.407s | 0m1.328s | 0m0.000s |

#### Reduce useless calculation

| input data      | real     | user     | sys      |
| --------------- | -------- | -------- | -------- |
| ellipse_N_00010 | 0m0.008s | 0m0.001s | 0m0.000s |
| ellipse_N_00100 | 0m0.011s | 0m0.005s | 0m0.000s |
| ellipse_N_00500 | 0m0.098s | 0m0.081s | 0m0.009s |
| ellipse_N_01000 | 0m0.356s | 0m0.335s | 0m0.010s |
| ellipse_N_02000 | 0m1.428s | 0m1.410s | 0m0.000s |




## References

- ChatGPT https://chatgpt.com/
