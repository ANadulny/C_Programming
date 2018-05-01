#ifndef BUFFER_H
#define BUFFER_H

#define MAX_SIZE 20
#define TRUE 1

#define PRODUCER 6 
#define CONSUMER 4 


#include <semaphore.h>


typedef struct Buffer
{
//SEMAPHORES
    sem_t MUTEX,  empty, full, producer, consumer;
//SYNCHRO VARIABLES
    int count;
//DATA
    int que[MAX_SIZE];
    unsigned int head, tail;

}Buffer;

void produce(Buffer*, unsigned int, int);
void take(Buffer*);

void producerN(Buffer*, int, int);
void consumerN(Buffer*, int, int);



#endif /* BUFFER_H */
