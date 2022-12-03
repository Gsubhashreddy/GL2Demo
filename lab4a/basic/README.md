# Tutorial for running your second mpi program

A FAQ is available at https://www.open-mpi.org/faq/?category=running

# Installing and Building

   Same as the hello program

   Build: `> mpicc basic.cpp -o basic`

# Apple M1

The brew installed gcc and open-mpi may have compat. errors associated
with mixing compilers. If you installed and built open-mpi with xcode,
you should compile with xcode.

## Running

   Running a program built with mpi, allows you to specify the 
   number of processes and the number of hosts (nodes). This 
   provides scaling of your problem. For this example, you will 
   run on your laptop (one node).

   Example: `> mpirun basic`


## Variations

   Note: Depending on what processor (number of cores), intel:  e.g., 
   i5, i7 (or ARM) will determine how many processes you can run
   you run. The default (variation a) will match the number of cores.

   a) Ensure processes run on the same node. The default is to maximize
      cores so, n = 1 MAY NOT be redundent. Consider when the number of 
      processes is less than cores of a node. The scheduler could use 
      under utilized nodes and spread your processes across multiple 
      nodes:

      `> mpirun -n 1 -c 2 basic`

      Verses

      `> mpirun -c 2 basic`


   a) Distribute four processes across two nodes (2 processes per node):
 
      `> mpirun -n 2 -c 4 basic`

   b) Undersubscribed: For CPU/memory intensive processes, assigning 
      a fewer number of processes than cores on each node s.t. each
      process is allocated a larger amount of memory or cores (threads).

      `> mpirun -n 2 -np 2 basic`

   c) Oversubscribing: Assigning more processes than cores on a node. Used
      in cases where I/O dominates processing needs. For instance, to have 
      four process on one node (2 cores). 

      ...
      > echo "localhost slots=4" > mpi.config
      > mpirun --hostfile mpi.config -n 2 -np 2 basic
      ...
