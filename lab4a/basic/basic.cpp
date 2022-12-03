#include <iostream>
//#include "omp.h"
#include "mpi.h"

int main(int argc, char** argv) {
    // debugging
    int verbose = 1;

    MPI_Init(NULL, NULL);

    int world_size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    if ( rank == 0 ) {
       printf("basic test with %d processes.\n\n",world_size);
    }

    /**
     * send messages to processes with a higher rank value.
     *
     * e.g., rank 0 sends messages to 1,2,3,...
     */

    MPI_Status status; // = MPI_SUCCESS;
    for ( int from = 0; from < world_size; from++ ) {
        int tag = from;
        //if ( rank == from ) { // send msgs and get response
        if ( rank == from ) { // send msgs and get response
            int value = from;
            for ( int to = from+1; to < world_size; to++ ) {
                if ( verbose )
                    printf("rank %03d sending check to %s (%03d)\n",
                           from, processor_name, to);

                MPI_Send(&value, 1, MPI_INT, to, tag, MPI_COMM_WORLD);
                MPI_Recv(&value, 1, MPI_INT, to, tag, MPI_COMM_WORLD, &status);
            }
        } else if ( rank > from ) { // receive msgs
            int value = 0;
            MPI_Recv(&value, 1, MPI_INT, from, tag, MPI_COMM_WORLD, &status);
            MPI_Send(&value, 1, MPI_INT, from, tag, MPI_COMM_WORLD);

            if ( verbose )
               printf("    ---> %03d received check from %03d\n",rank, from);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank==0)
        printf("Send-Recv test on %d processes PASSED.\n", world_size);


    MPI_Finalize();
}
