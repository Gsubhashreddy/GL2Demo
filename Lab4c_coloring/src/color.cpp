/**
 * Modification to hello to organize processes into multiple sub-domains (groups)
 **/

#include <iostream>
//#include "omp.h"
#include "mpi.h"

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // we now split the world into two communication groups
    int color = world_rank % 2;
    MPI_Comm my_comm;
    MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &my_comm);

    int local_size, local_rank;
    MPI_Comm_size(my_comm, &local_size);
    MPI_Comm_rank(my_comm, &local_rank);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    std::cout << "node:" << processor_name 
              << ", rank: " << local_rank 
              << " of " << color
              << ", world rank: " << world_rank 
              << " of " << world_size << std::endl;  
           
    MPI_Finalize();
}
