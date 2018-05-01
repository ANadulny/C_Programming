#include "Buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

int main()
{
    int pid;

    int fd = shm_open("Buffer", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(fd, sizeof(Buffer));
    Buffer* buf = (Buffer*)mmap(NULL, sizeof(Buffer), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    sem_init( &(buf->MUTEX)  ,1 , 1);
    sem_init( &(buf->full) ,1 , 0);
    sem_init( &(buf->empty) ,1 , MAX_SIZE);
    sem_init( &(buf->producer) ,1 , 1);
    sem_init( &(buf->consumer) ,1 , 1);	


    buf->count=0;
    buf->head=0;
    buf->tail=0;
	
	int j;
	int num;
		
	for(j=0; j<PRODUCER; j++)
	{
		num = PRODUCER - j;
		
		pid = fork();
		if(pid == 0)
		{
			printf("Launching producer%d\n", j+1);
			producerN(buf, num, j+1);
		}
	}
	
	
	for(j=1; j<CONSUMER; j++)
	{
		num = j * 2;
		
		pid = fork();
		if(pid == 0)
		{
			printf("Launching consumer%d\n", j);
			consumerN(buf, num, j);
		}

	}
	
	printf("Launching consumer%d\n", CONSUMER);
	consumerN(buf, CONSUMER*2, CONSUMER);

    return 0;
}


void producerN(Buffer* buf, int num, int item)
{
    
    int i;
    while(TRUE)
    {
        sleep(1);
        printf("Producer%d tries to enter critical section\n", item);
        //CRITICAL SECTION
	sem_wait((&buf->producer));

	for(i=0; i<num; i++)
        {
		sem_wait((&buf->empty));
	}
        sem_wait( &(buf->MUTEX) );
        printf("Producer%d entered critical section\n", item);
	
        for(i=0; i<num; i++)
        {
            produce(buf, buf->tail, item);
            ++(buf->count);
            sem_post(&(buf->full));
        }
        printf("Producer%d adds %d items           %d\n", item, num, buf->count);

	sem_post((&buf->producer));
        printf("Producer%d leaves critical section\n", item);
        sem_post(&(buf->MUTEX));
        //CRITICAL SECTION END;
	
    }
}


void consumerN(Buffer* buf, int num, int index)
{
    int i=0;
    while(TRUE)
    {
        sleep(1);
        printf("Consumer%d tries to enter critical section\n", index);
        //CRITICAL SECTION
		
	sem_wait((&buf->consumer));
	for(i=0; i<num; i++)
        {
		sem_wait(&(buf->full));
	}
        sem_wait(&(buf->MUTEX) );
        printf("Consumer%d entered critical section\n",index);
        for(i=0; i<num; i++)
        {
            take(buf);
            --(buf->count);
            sem_post(&(buf->empty));
        }
	sem_post((&buf->consumer));
        printf("Consumer%d takes %d items           %d\n",index, num, buf->count);

        printf("Consumer%d leaves critical section\n", index);
        sem_post(&(buf->MUTEX));
	
    }
}

// BUFFER
void produce(Buffer* buf, unsigned int tail, int item)
{
   buf->que[tail] = item;
   buf->tail = ((buf->tail)+1) %(MAX_SIZE);

}

void take(Buffer* buf)
{
   buf->head = ((buf->head)+1) %(MAX_SIZE);
}


