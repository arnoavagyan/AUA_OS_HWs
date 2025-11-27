#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


long long counter = 0;

pthread_spinlock_t spinLock;

void* increment(void* arg)
{
    int M = *(int*)arg;
    for (int i = 0; i < M; i++) 
    {
        pthread_spin_lock(&spinLock);    // Acquire the mutex
        counter++;
        pthread_spin_unlock(&spinLock);  // Release the mutex
    }
    return NULL;
}

int main()
{
    int N = 4;
    int M = 1000000;

    pthread_spin_init(&spinLock,  PTHREAD_PROCESS_PRIVATE);

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
    
    if (pthread_spin_destroy(&spinLock) != 0) 
    {
        perror("Failed to destroy spinlock");
        return 1;
    }
    
    return 0;
}
