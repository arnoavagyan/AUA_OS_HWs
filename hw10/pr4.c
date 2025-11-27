#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


sem_t semA, semB, semC;

void* thread_A_func(void* arg)
{
    int N = *(int*)arg;
    for (int i = 0; i < N; i++)
    {
        sem_wait(&semA);
        printf("Thread A: A %d\n", i);
        sem_post(&semB);
    }
    return NULL;
}

void* thread_B_func(void* arg)
{
    int N = *(int*)arg;
    for (int i = 0; i < N; i++)
    {
        sem_wait(&semB);
        printf("Thread B: B %d\n", i);
        sem_post(&semC);
    }
    return NULL;
}

void* thread_C_func(void* arg)
{
    int N = *(int*)arg;
    for (int i = 0; i < N; i++)
    {
        sem_wait(&semC);
        printf("Thread C: C %d\n", i);
        sem_post(&semA);
    }
    return NULL;
}

int main()
{
    pthread_t thread_A, thread_B, thread_C;
    int N = 10;

    sem_init(&semA, 0, 1); // A starts first
    sem_init(&semB, 0, 0);
    sem_init(&semC, 0, 0);

    if (pthread_create(&thread_A, NULL, thread_A_func, &N) != 0) 
    {
        perror("Failed to create thread A");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread_B, NULL, thread_B_func, &N) != 0) 
    {
        perror("Failed to create thread B");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread_C, NULL, thread_C_func, &N) != 0) 
    {
        perror("Failed to create thread C");
        exit(EXIT_FAILURE);
    }
    if (pthread_join(thread_A, NULL) != 0) 
    {
        perror("Failed to join thread A");
        exit(EXIT_FAILURE);
    }
    if (pthread_join(thread_B, NULL) != 0)
    {
        perror("Failed to join thread B");
        exit(EXIT_FAILURE);
    }
    if (pthread_join(thread_C, NULL) != 0)
    {
        perror("Failed to join thread C");
        exit(EXIT_FAILURE);
    }
    sem_destroy(&semA);
    sem_destroy(&semB);
    sem_destroy(&semC);
    return 0;
}