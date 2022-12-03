/*
 * A simple example to show how rank (ID) is used to divide large 
 * data sets into smaller sets.
 *
 * LAB:
 * See 'TODO' for lab work - extend/change code to perform suggested changes.
 */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>

//#include "omp.h"
#include "mpi.h"



int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    // we use the world to determine which setup (./data) is used, and rank to 
    // assgn the subset of data to a process

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // processor name is not important in most sub-dividing
    // work. However, we can use it to determine which
    // processes reside on the same computer.

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    std::cout << "Process Info: from " << processor_name 
              << ", rank: " << world_rank 
              << " of " << world_size << std::endl;  
           
    // initialization to minimize reading common 
    // configuration settings
    if ( argc < 3 ) {
      throw std::invalid_argument( "Invalid number of args to main. main base_input_dir base_output_dir" );
    }

    std::string dataDir(argv[1]);
    //main_args.assign(argv + 1, argv + argc);

    // TODO add a configuration file that is read by rank 0 only, and sent to all other processes.
    if ( world_rank == 0 ) { 
      /** open file: data_0.txt */ 
    }
    else { 
      /** do this */ 
    }

    // TODO:
    //   1. this is not the best - why? what would you change this to?
    //   2. how do you handle different world sizes?

    std::string rankDataFile(argv[1]);
    rankDataFile += "/" + std::to_string(world_size) + "/" + std::to_string(world_rank) + ".dat";
    std::cout << "reading " << rankDataFile << std::endl;

    // load in data 
    std::vector<int> inputData;
    try {
       std::ifstream ifs(rankDataFile);
       std::string raw;
       while (std::getline(ifs,raw)) {
         // ...assuming file has only integers...
         inputData.push_back(std::stoi(raw));

         std::cout << "rank " << world_rank << " input: " << raw << std::endl;
       }
       ifs.close();
    } catch (std::exception& e) {
       std::cerr << "ERROR: reading data: " << e.what() << std::endl;
    }

    // TODO: move to another source file
    std::vector<int> workData;
    for (auto v : inputData) {
       // dummy work
       workData.push_back(v * 10);
    }

    // -------------------------------------------------------------------------
    // NOTES:
    // 1. if the data was too big to fit into one process' memory, gathering is 
    //    really a bad idea!
    // 2. if processes write all at once, it could overload the file system!
    // -------------------------------------------------------------------------

    // TODO 
    //   1) move to another source file
    //   2) implement baton-passing algo to limit file system overload

    // write outputs for each file.  
    try {
      // NOTE: using a different organization (naming) than what was used for input files. 
      // This shows another strategy for file organization though we could run into i-node 
      // issues with very large runs." 

      std::stringstream outData;
      outData << argv[2] << "/" \
              << std::setfill('0') << std::setw(3) << std::to_string(world_size) << "-" \
              << std::setfill('0') << std::setw(3) << std::to_string(world_rank) \
              << ".dat" << std::ends;

      std::cout << "writing " << outData.str() << std::endl;
      std::ofstream ofs(outData.str(),std::ofstream::out);
      for (auto v : workData) {
        ofs << v << std::endl;
      }
      ofs.close();
    } catch (std::exception& e) {
       std::cerr << "ERROR: writing data: " << e.what() << std::endl;
    }

    // TODO move closing operations to another source file

    // sync processes after completing work to coordinate closing steps
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();
}
