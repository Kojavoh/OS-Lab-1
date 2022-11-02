// Chris Hartmann
// KSU Fall 2022 Operating Systems
// Lab 1: consumer.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>

void exitError(char* errMsg, int* table, int tbl, sem_t* CanConsume, sem_t* CanProduce, sem_t* Mutex);

void close_all(int* table, int tbl, sem_t* CanConsume, sem_t* CanProduce, sem_t* Mutex);

int main() {
    // Create Table/Collect Shared Data
    int tbl = shm_open("table", O_CREAT | O_RDWR, 0666);
    ftruncate(tbl, sizeof(int));
    int* table = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, tbl, 0);

    // Remove semaphore identifier relation
    /*sem_unlink("CanConsume");
    sem_unlink("CanProduce");
    sem_unlink("Mutex");*/

    // Open Semaphores
    // Semaphore to track if there are items in the table to consume
    sem_t* CanConsume = sem_open("/CanConsume", O_CREAT, 0666, 0);
    
    // Semaphore to track if there is room in the table to produce another item
    sem_t* CanProduce = sem_open("/CanProduce", O_CREAT, 0666, 2);
    
    // Semaphore to lock the critical section
    sem_t* Mutex = sem_open("/Mutex", O_CREAT, 0666, 1);

    int iterations = 10; // An arbitrary restriction placed on the loop to prevent infinite work
    printf("\nConsumer ready to receive items from producer\n");

    // Loop to complete work
    for(int i = 0; i < iterations; i++) {
        // Block consumer until at least one item exists in table
        if(sem_wait(CanConsume) != 0) {
            exitError("Failure in sem_post(CanConsume)\n", table, tbl, CanConsume, CanProduce, Mutex);
        }

        // Sleep 
        int seconds = rand() % 2 + 1;
        sleep(seconds);
        
        // Request to enter, perform, and signal exit of the critical section
        if(sem_wait(Mutex) != 0) {
            exitError("Failure in sem_wait(Mutex)\n", table, tbl, CanConsume, CanProduce, Mutex);
        }
        (*table)--;
        if(sem_post(Mutex) != 0) {
            exitError("Failure in sem_post(Mutex)\n", table, tbl, CanConsume, CanProduce, Mutex);
        }

        printf("Item Consumed, %d item(s) left remaining in the table.\n", *table);
        
        // Signal that an additional item can be produced
        if(sem_post(CanProduce) != 0) {
            exitError("Failure in sem_post(CanProduce)\n", table, tbl, CanConsume, CanProduce, Mutex);
        }
    }

    close_all(table, tbl, CanConsume, CanProduce, Mutex);

    printf("Consumer finished!\n");
    return 0;
}

void exitError(char* errMsg, int* table, int tbl, sem_t* CanConsume, sem_t* CanProduce, sem_t* Mutex) {
    printf("%s", errMsg);
    close_all(table, tbl, CanConsume, CanProduce, Mutex);
    exit(-1);
}

void close_all(int* table, int tbl, sem_t* CanConsume, sem_t* CanProduce, sem_t* Mutex) {
    // Close semaphore variables
    sem_close(CanConsume);
    sem_close(CanProduce);
    sem_close(Mutex);

    // Remove semaphore identifier relation
    sem_unlink("CanConsume");
    sem_unlink("CanProduce");
    sem_unlink("Mutex");

    // Deallocate, close, and unidentify table objects
    munmap(table, sizeof(int));
    close(tbl);
    shm_unlink("table");
}
