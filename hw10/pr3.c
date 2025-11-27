#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>

#define BUFFER_SIZE 8
#define P 4
#define C 4
int buffer[BUFFER_SIZE];
int in_pos = 0;
int out_pos = 0;
int produced_consumed_count = 0;

sem_t empty_slots;
sem_t full_slots;

pthread_mutex_t buffer_mutex;

void printBufferState()
{
    printf("Buffer state: [");
    for (int i = 0; i < BUFFER_SIZE; i++) 
    {
        printf("%d", buffer[i]);
        if (i < BUFFER_SIZE - 1) 
        {
            printf(", ");
        }
    }
    printf("]\n");
}

void* producerFunction(void *arg)
{
    int random_num = rand();

    sem_wait(&empty_slots);

    if (produced_consumed_count > P * C / 4)
    {
        printf("Producer exiting: produced_consumed_count = %d\n", produced_consumed_count);
        return NULL;
    }

    pthread_mutex_lock(&buffer_mutex);

    ++produced_consumed_count;

    buffer[in_pos] = random_num;
    in_pos = (in_pos + 1) % BUFFER_SIZE;

    printBufferState();

    pthread_mutex_unlock(&buffer_mutex);

    sem_post(&full_slots);

    return NULL;
}  

void* consumerFunction(void* arg)
{

    sem_wait(&full_slots);

    if (produced_consumed_count > P * C / 4)
    {
        printf("Consumer exiting: produced_consumed_count = %d\n", produced_consumed_count);
        return NULL;
    }

    pthread_mutex_lock(&buffer_mutex);

    ++produced_consumed_count;

    buffer[out_pos] = 0;
    out_pos = (out_pos + 1) % BUFFER_SIZE;

    printBufferState();
    
    pthread_mutex_unlock(&buffer_mutex);

    sem_post(&empty_slots);
    return NULL;
}


int main()
{

    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);

    pthread_mutex_init(&buffer_mutex, NULL);

    pthread_t producers[P];
    pthread_t consumers[C];

    for (int i = 0; i < P; i++) 
    {
        if (pthread_create(&producers[i], NULL, producerFunction, NULL) != 0) 
        {
            perror("Failed to create producer thread");
            return 1;
        }
    }
    for (int i = 0; i < C; i++) 
    {
        if (pthread_create(&consumers[i], NULL, consumerFunction, NULL) != 0) 
        {
            perror("Failed to create consumer thread");
            return 1;
        }
    }
    for (int i = 0; i < P; i++) 
    {
        if (pthread_join(producers[i], NULL) != 0) 
        {
            perror("Failed to join producer thread");
            return 1;
        }
    }
    for (int i = 0; i < C; i++)
    {
        if (pthread_join(consumers[i], NULL) != 0) 
        {
            perror("Failed to join consumer thread");
            return 1;
        }
    }
    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    pthread_mutex_destroy(&buffer_mutex);

    return 0;
}