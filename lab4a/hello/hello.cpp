// Ref: http://mpitutorial.com/tutorials/mpi-hello-world/

#include <iostream>
//#include "omp.h"
#include "mpi.h"

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    std::cout << "hello from " << processor_name 
              << ", rank: " << world_rank 
              << " of " << world_size << std::endl;  
           
    if ( world_rank == 0 ) { 
      /** open file: data_0.txt */ 
    }
    else if ( world_rank == 2 ) { /** do this */ }

    MPI_Finalize();
}
