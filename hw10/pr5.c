#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


sem_t printer;

int counter = 0;

pthread_mutex_t counter_mutex;

void* print(void* arg)
{
    int id = *((int*)arg);
    sem_wait(&printer);
    
    printf("Thread %d is printing...\n", id);
    
    pthread_mutex_lock(&counter_mutex);
    counter++;
    int current = counter;
    printf("Number of threads in printing section: %d\n", counter);
    pthread_mutex_unlock(&counter_mutex);

    usleep(2000000);

    pthread_mutex_lock(&counter_mutex);
    counter--;
    pthread_mutex_unlock(&counter_mutex);

    sem_post(&printer);
     
    return NULL;
}

int main()
{
    int k = 3;
    int N = 5;
    pthread_t threads[N];
    sem_init(&printer, 0, k);
    pthread_mutex_init(&counter_mutex, NULL);

    int ids[N];
    for (int i = 0; i < N; i++) 
    {
        ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, print, &ids[i]) != 0) 
        {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < N; i++) 
    {
        if (pthread_join(threads[i], NULL) != 0) 
        {
            perror("Failed to join thread");
            exit(EXIT_FAILURE);
        }
    }
}