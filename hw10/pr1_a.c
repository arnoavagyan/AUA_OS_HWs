#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long long counter = 0;

void* increment(void* arg)
{
    int M = *(int*)arg;
    for (int i = 0; i < M; i++) 
    {
        counter++;
    }
    return NULL;
}

int main()
{
    int N = 4;
    int M = 1000000;

    pthread_t threads[N];
    for (int i = 0; i < N; i++) 
    {
        if (pthread_create(&threads[i], NULL, increment, &M) != 0) 
        {
            perror("Failed to create thread");
            exit(1);
        }
        if (pthread_join(threads[i], NULL) != 0) 
        {
            perror("Failed to join thread");
            exit(1);
        }
    }
    printf("The value of counter: %lld\n", counter);
    printf("Expected value: %d\n", N * M);
    return 0;
}