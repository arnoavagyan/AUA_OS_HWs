#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print(void* arg)
{
    int thread_id = *((int*)arg);
    printf("Thread %d is running... ", thread_id);
    for (int i = 1; i <= 5; i++) 
    {
        printf("%d ", i);
    }
    printf("\n");
    return NULL;
}

int main()
{
    pthread_t t1, t2, t3;
    int id1 = 1, id2 = 2, id3 = 3;

    if (pthread_create(&t1, NULL, print, &id1) != 0) 
    {
        perror("Failed to create thread 1");
        exit(1);
    }
    if (pthread_create(&t2, NULL, print, &id2) != 0) 
    {
        perror("Failed to create thread 2");
        exit(1);
    }
    if (pthread_create(&t3, NULL, print, &id3) != 0) 
    {
        perror("Failed to create thread 3");
        exit(1);    
    }
    if (pthread_join(t1, NULL) != 0) 
    {
        perror("Failed to join thread 1");
        return 1;
    }

    if (pthread_join(t2, NULL) != 0) 
    {
        perror("Failed to join thread 2");
        return 1;
    }

    if (pthread_join(t3, NULL) != 0) 
    {
        perror("Failed to join thread 3");
        return 1;
    }
}