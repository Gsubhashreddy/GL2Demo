# Tutorial for running your first mpi program

A FAQ is available at https://www.open-mpi.org/faq/?category=running

# Apple M1 architectures

Use xcode if you have built mpi with xcode. I am seeing compat. errors
with mixing xcode and gcc built code either at compile or runtime.

Notes: 
   * brew installed gcc/g++ is failing on include directory paths. You 
     should use xcode for building. 
   * runtime errors on uncaught exception can occur. 

# Installing and Building

   a) install gcc 11.x (or latest version)
   b) install open-mpi (note M1 using brew to install open-mpi 
      will install into it's own directory), you will want to
      be careful with which CC is used to compile the libraries.

      Example: > brew update open-mpi

   c) building:

      Build: `> mpicc hello.c -o hello`

# Running

   Running a program built with mpi, allows you to specify the 
   number of processes and the number of hosts (nodes). This 
   provides scaling of your problem. For this example, you will 
   run on your laptop (one node).

   Example: `> mpirun hello`


## Variations

   a) maximum processes (cores) for a two core node (same as above):

      ...
      > mpirun -n 1 -c 2 hello
      ...

   a) launch four processes, two on each node:

      ...
      > mpirun -n 2 -c 4 hello
      ...

   b) Undersubscribed: one process on each node. This maximizes the 
      amount of memory the process has available.

      ...
      > mpirun -n 2 -np 2 hello
      ...

   c) Oversubscribed: four process on one node (2 cores). This can
      occur if each process has IO waits and do not exceed physical
      memory.

      ...
      > echo "localhost slots=4" > mpi.config
      > mpirun --hostfile mpi.config -n 2 -np 2 hello
      ...
