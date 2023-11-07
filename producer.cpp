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
int main () {
    const char *name = "Shared Memory";
    const char *fill_semaphore = "Full";
    const char *avail_sempahore = "Available";
    const char *mutex_semaphore = "Mutex";
    const int MAX_TABLE_QUANTITY = 2;
    sem_t *fill, *available, *mutex;
    int shared_memory_file_descriptor;
    int *table;
    int loop_count = 5;
}