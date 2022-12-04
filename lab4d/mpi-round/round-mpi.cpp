#include <iostream>
#include <iomanip>
#include <random>
#include "mpi.h"

// (un)comment to show allreduce vs reduce
#define S_ALLREDUCE

/**
 * @brief basic boost chrono
 *
 * To build:
 * mpic++ -std=c++14 round-mpi.cpp -o round-mpi
 *
 * To run:
 * mpirun -n N round-mpi
 * mpirun -n N --oversubscribe round-mpi
 * mpirun -n N  -hostfile mpi.config round-mpi
 *
 *
 * Tuning:
 * By default openmpi runtime uses the best communication between processes,
 * network or shared memory (only on the same node). A list of parameters
 * can be found at https://www.open-mpi.org/faq/?category=tuning
 *
 * Tuning the number of processes to run and the communication's byte transfer 
 * layer (btl) and overload without causing errors in the shared memory (vador)
 * configuration:
 *
 * mpirun -n 36 --oversubscribe --mca btl self,tcp b/round-mpi
 *
 * try running without the --mca btl self,tcp.
 *
 *
 *      Author: gash
 */
int main(int argc, char **argv) {

    MPI_Init(NULL, NULL);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);


    // we seed to create a consistent random number
    auto seed = (double)world_rank * 0.001f;

    std::default_random_engine generator;
    generator.seed(seed);

    std::uniform_real_distribution<double> distr(0.0, 1.0);
    auto val = distr(generator);
 
    // NOTE: we should not have to do this! Seed should have given us a 
    //       new number per rank!

    for (int n = 0; n < world_rank; n++)
       val = distr(generator);

    // everyone will get the results
    auto world_sum = (double)0.0f;

#ifdef S_ALLREDUCE
    MPI_Allreduce(&val, &world_sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
#else
    MPI_Reduce(&val, &world_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
#endif

// NOTE we are not getting the correct value for reduce!
// SOL: use a allgather to sum up individual values

#ifndef S_ALLREDUCE
    if ( world_rank == 0 ) 
#endif
    std::cout << "rank: " << world_rank 
              << ", value = " << std::setprecision(15) 
              << ", seed  = " << std::setprecision(15)
              << ", world = " << std::setprecision(15) << world_sum << std::endl;

    MPI_Finalize();
}
