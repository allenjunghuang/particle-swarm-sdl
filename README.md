# Particle Swarm Optimization

This application simulates the partical motion with Simple DirectMedia Layer (SDL).

## Particle Swarm Optimization

PSO is a kind of evolutionary algorithm inspired by social behavior of bird flocking or fish schooling. For numerical optimization problem, the potential solutions, called particles, fly through the problem space by following the current optimum particles.

The optimization process is given by

1. Initialize the swarm from the solution space
2. Evaluate fitness of individual particles
3. Update _gbest_, _pbest_ and velocity

and repeat step 2 and 3 until convergence or the stopping condition is satisfied.

There are three fitness functions for single objective optimization:
- Sphere function

    It is the easiest one with a convex function.

- Ackley function

    The intermediate task with a non-convex function.

- Rastrigin function

    Finding the minimum of this non-convex function is a difficult problem due to its large search space and its large number of local minima.

Reference
1. https://en.wikipedia.org/wiki/Test_functions_for_optimization
2. https://jamesmccaffrey.wordpress.com/2015/06/09/particle-swarm-optimization-using-python/