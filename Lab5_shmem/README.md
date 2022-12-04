# Shared Memory Synchronization

This example demonstrates the use of shared memory to convey data between
a server and a number of clients.

The server uses a simple monotonically increasing version number to indicate
there has been a change in the data. Obviously, the payload has been simplified
for the demonstration. Likewise, the client's acknowledgement of the ending of
the data sharing with the character 'z' in the ack field is also for
demonstration.

## Building

### Indivdually

 To compile the server:

```
 gcc shm-server.c -o shm-server
 gcc shm-client.c -o shm-client
```

### Cmake

Be sure to modify the CMakeLists.txt to specify your compiler

```
> mkdir build
> cd buld
> cmake ..
> make
```

## Running

 In two separate terminals (xterm) start the server first then the client. Note
 if the client is started first, the process will fail as the shared memory
 segment has not been created by the server.
