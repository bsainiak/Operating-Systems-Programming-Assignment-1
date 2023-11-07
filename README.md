# Operating-Systems-Programming-Assignment-1

Hello! This program is a solution to the producer and consumer problem using semaphores and shared memory.
The producer consumer problem is where one process produces an item and another process consumes the object.
This solution uses a bounded buffer for the storage of shared data.
These processes are designed to run concurrently and should avoid data inconsistency with the semaphores.

# Usage

In order to run these processes you need to use the commands
$ g++ producer.cpp -pthread -lrt -o producer
$ g++ consumer.cpp -pthread -lrt -o consumer
$ ./producer & ./consumer &