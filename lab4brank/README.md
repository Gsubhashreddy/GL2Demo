# Using rank to access data

This lab looks at how to setup and manage large data sets. Your goal is to 
modify the existing code by completing the 'TODO' sections

## apple M1 

Notes: 
   * brew installed gcc/g++ is failing on include directory paths. You 
     should use xcode for building. 
   * runtime errors on uncaught exception can occur. 

## building

```bash
mkdir build
cd build
cmake ..
```

If you choose to use boost, you will need to use a command like:

```bash
cmake -DBOOST_ROOT=~/usr/local/gcc/boost/boost_1_72_0 ..
```

## running

The executable (rank) requires two commandline arguments (input 
directory and output directory).

```bash
mpiexec -n 2 ./rank <somepath> <anotherpath>

mpiexec -n 2 ./rank ../data ../out
```
