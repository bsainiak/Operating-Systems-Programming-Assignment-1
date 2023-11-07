//Brandon Sainiak Operating Systems Project 1

#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>


/* Information taken from 
    https://man7.org/linux/man-pages/man3/shm_open.3.html
*/

void PrintSemaphoreValue(std::string name, sem_t *semaphore, int &value);

int main () {
    const char *name = "Shared Memory";
    const char *fill_semaphore = "Full";
    const char *avail_sempahore = "Available";
    const char *mutex_semaphore = "Mutex";
    sem_t *fill, *available, *mutex;
    int shared_memory_file_descriptor;
    int *table;
    int loop_count = 5;

    // Make shared process between prod and cons
    shared_memory_file_descriptor = shm_open(name, O_CREAT | O_RDWR, 0666);

    // Set the size of the mem space
    ftruncate(shared_memory_file_descriptor,sizeof(int));

}