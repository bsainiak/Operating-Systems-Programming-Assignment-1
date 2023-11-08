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
    //initializes variables to be used with shared memory
    const char *name = "Shared Memory";
    const char *fill_semaphore = "Full";
    const char *avail_semaphore = "Available";
    const char *mutex_semaphore = "Mutex";
    sem_t *fill, *available, *mutex;
    int shared_memory_file_descriptor;
    int *table;
    int loop_count = 5;

    //Shared memory
    shared_memory_file_descriptor = shm_open(name, O_CREAT | O_RDWR, 0666);

    //sets the size of the shared memory
    ftruncate(shared_memory_file_descriptor,sizeof(int));

    //maps the processes together
    table = (int *)mmap(0,sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shared_memory_file_descriptor, 0);

    //Creates 3 semaphores to be used in the processes
    fill = sem_open(fill_semaphore, O_CREAT,0666,0);
    
    available = sem_open(avail_semaphore, O_CREAT, 0666, 3);

    mutex = sem_open(mutex_semaphore,O_CREAT,0666,1);

    int value = -1;
    //decrements the loop_count so the process doesn't run forever
    while(loop_count--){
        //prevents deadlock
        sem_wait(fill);
        sleep(rand()%2+1);
        sem_wait(mutex);
        (* table)--; //critical section
        sem_post(mutex);
        std::cout << "Consumer: Consumes an item. There are " << *table << " item(s).\n";
        sem_post(available);
    }
    std::cout << "----------------------------------------------\n";
    std::cout << "CONSUMER: Cycle limit. " << *table << " product(s) are left.\n";
    std::cout << "----------------------------------------------\n";
    
    //frees semaphores and shared memory
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

void PrintSemaphoreValue(std::string name, sem_t *semaphore, int &value) {
    std::cout << name << " value: " << sem_getvalue(semaphore, &value) << std::endl;
}