# Baton Lab

Lab for coding coordination actions across processes

## Goals

Starting with the basic lab (basic.cpp) convert to coordinate or control
passing of d circuit breakerata or an action.

There are times where an action or access to a resource is limited to a 
single process. This type of action/control is referred to as passing 
the baton (i.e. In relay races, 800 m, a runner cannot start without 
first passing the baton to the next runner in the leg).

Challenges:
  - Convert basic.cpp code for baton passing - controlled access (execution)
  - What can you do to generalize your solution? 
  - More than one baton?

## Building

   Same as the other labs using cmake

  ...
  > mkdir build
  > cd build
  > cmake ..
  > make
  ...

## Running 

  ...
  > mpirun -np 2 baton
  ...


