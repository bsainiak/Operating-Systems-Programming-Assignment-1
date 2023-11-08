# Operating-Systems-Programming-Assignment-1

Hello! This program is a solution to the producer and consumer problem using semaphores and shared memory.
The producer consumer problem is where one process produces an item and another process consumes the object.
This solution uses a bounded buffer for the storage of shared data.
These processes are designed to run concurrently and should avoid data inconsistency with the semaphores.
The current version of the program produces and consumes 5 sets of data

# Problem

Specifically this program was created to solve this form of the producer consumer problem.
The producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is complete, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize producer and consumer.  Mutual exclusion should be considered. We use threads in the producer program and consumer program. Shared memory is used for the “table”.

# Usage

In order to run these processes you need to use the commands within a Linux Terminal.
You also need to download the two processes together so that they can be ran concurrently.
The first 2 commands create a producer and consumer executables that are then executed by the final command.
$ g++ producer.cpp -pthread -lrt -o producer
$ g++ consumer.cpp -pthread -lrt -o consumer
$ ./producer & ./consumer &

A typical output should look similar to this:
PRODUCER: Produce an item. There are 1 item(s).
PRODUCER: Produce an item. There are 2 item(s).
***   PRODUCER TABLE FULL   ***
CONSUMER: Consume an item. There are 1 item(s).
PRODUCER: Produce an item. There are 2 item(s).
***   PRODUCER TABLE FULL   ***
CONSUMER: Consume an item. There are 1 item(s).
PRODUCER: Produce an item. There are 2 item(s).
***   PRODUCER TABLE FULL   ***
CONSUMER: Consume an item. There are 1 item(s).
PRODUCER: Produce an item. There are 2 item(s).
***   PRODUCER TABLE FULL   ***
----------------------------------------------
PRODUCER: Cycle limit. 2 product(s) are left.
----------------------------------------------
CONSUMER: Consume an item. There are 1 item(s).
CONSUMER: Consume an item. There are 0 item(s).
----------------------------------------------
CONSUMER: Cycle limit. 0 product(s) are left.
----------------------------------------------

