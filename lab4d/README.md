## MPI's version of the rounding lab

Welcome to the OpenMPI's version of the threading lab's rounding
example code (lab). Here we are looking to see how multiple processes
interact.

The key focus on this lab is to see if there are behaviors in the 
communication between processes. Secondarily, we will look at how
to oversubscribe (run more processes) and underscribe a node.

### Building by hand (intel-based)

```
mpic++ -std=c++14 round-mpi.cpp -o round-mpi
```

### Building with Cmake (ARM and intel-based)

```
> mkdir build
> cd build
> cmake ..
> make
```

### Running

Specifying the number of process (-n, -np)

Using the maximum number of processes (cores)

```
mpirun round-mpi
```

Over(Under)-subscribing the number of processes

```
mpirun -n N --oversubscribe round-mpi
```

### Tuning

Tuning the number of processes to run and the communication's byte transfer 
layer (btl) and overload without causing errors in the shared memory (vador)
configuration:

mpirun -n N  -hostfile mpi.config round-mpi

Tuning:
By default openmpi runtime uses the best communication between processes,
network or shared memory (only on the same node). A list of parameters
can be found at https://www.open-mpi.org/faq/?category=tuning

```
mpirun -n 36 --oversubscribe --mca btl self,tcp b/round-mpi
```

Try running without the --mca btl self,tcp for n > number of cores.


#### Other tuning parameters

TBD

