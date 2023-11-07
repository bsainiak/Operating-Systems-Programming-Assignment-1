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
int main () {
    const char *name = "Shared Memory";
    const char *fill_semaphore = "Full";
    const char *avail_semaphore = "Available";
    const char *mutex_semaphore = "Mutex";
    const int MAX_TABLE_QUANTITY = 2;
    sem_t *fill, *available, *mutex;
    int shared_memory_file_descriptor;
    int *table;
    int loop_count = 5;

        // Creates the Shared memory between processes
    shared_memory_file_descriptor = shm_open(name, O_CREAT | O_RDWR, 0666);

    // Sets the size of the memory space
    ftruncate(shared_memory_file_descriptor,sizeof(int));

    table = (int *)mmap(0,sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shared_memory_file_descriptor, 0);

    //Initializes the semaphore
    fill = sem_open(fill_semaphore, O_CREAT,0666,0);
    
    available = sem_open(avail_semaphore, O_CREAT, 0666, 3);

    mutex = sem_open(mutex_semaphore,O_CREAT,0666,1);

    //begins the production loop
    std::cout << "\n" << std::endl;
    while(loop_count--){
        sem_wait(available);
        sleep(rand()%2+1);
        sem_wait(mutex);
        
        //limit table size
        if(*table < MAX_TABLE_QUANTITY){
            (* table)++;
            std::cout << "Producer: Produces an item. There are " << *table << " item(s).\n";
            sem_post(mutex); 
            sem_post(fill);

            if (*table == MAX_TABLE_QUANTITY){
                std::cout << "***   TABLE FULL   ***\n";
            }
        } 
    }

    std::cout << "----------------------------------------------\n";
    std::cout << "PRODUCER: Cycle limit. " << *table << " product(s) are left.\n";
    std::cout << "----------------------------------------------\n";
    
   
        
    // Close Semaphores and Remove Shared memory
    sem_close(fill);
    sem_close(available);
    sem_close(mutex);
    sem_unlink(fill_semaphore);
    sem_unlink(avail_semaphore);
    sem_unlink(mutex_semaphore);

    
    munmap(table, sizeof(int));
    close(shared_memory_file_descriptor);
    shm_unlink(name);

    return 0;
}