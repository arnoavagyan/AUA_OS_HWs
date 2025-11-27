# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

long long balance = 0;

pthread_mutex_t mutex;
pthread_spinlock_t spinLock;

#define USE_MUTEX 0
#define USE_SPINLOCK 1
#define SHORT_CRITICAL_SECTION 0
#define LONG_CRITICAL_SECTION 1

void* depositFunction(void* arg) 
{
    # if USE_MUTEX
    {
        pthread_mutex_lock(&mutex);
    } 
    # elif USE_SPINLOCK 
    {
        pthread_spin_lock(&spinLock);
    }
    # endif
    balance++;
    # if LONG_CRITICAL_SECTION
    {
        usleep(100);
    }
    # endif
    # if USE_MUTEX 
    {
        pthread_mutex_unlock(&mutex);
    } 
    # elif USE_SPINLOCK 
    {
        pthread_spin_unlock(&spinLock);
    }
    # endif
    return NULL;
}
void* withdrawFunction(void* arg) 
{
    # if USE_MUTEX
    {
        pthread_mutex_lock(&mutex);
    } 
    # elif USE_SPINLOCK
    {
        pthread_spin_lock(&spinLock);
    }
    # endif
    balance--;
    # if LONG_CRITICAL_SECTION
    {
        usleep(100);
    }
    # endif
    # if USE_MUTEX
    {
        pthread_mutex_unlock(&mutex);
    } 
    # elif USE_SPINLOCK
    {
        pthread_spin_unlock(&spinLock);
    }
    # endif
    return NULL;
}

int main()
{
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    #if USE_MUTEX
        pthread_mutex_init(&mutex, NULL);
    #elif USE_SPINLOCK
        pthread_spin_init(&spinLock, PTHREAD_PROCESS_PRIVATE);
    #endif
    
    int dN = 5;
    int wN = 5;

    pthread_t deposit_threads[dN];
    pthread_t withdraw_threads[wN];

    for (int i = 0; i < dN; i++) 
    {
        if (pthread_create(&deposit_threads[i], NULL, depositFunction, NULL) != 0) 
        {
            perror("Failed to create deposit thread");
            return 1;
        }
    }
    for (int i = 0; i < wN; i++) 
    {
        if (pthread_create(&withdraw_threads[i], NULL, withdrawFunction, NULL) != 0) 
        {
            perror("Failed to create withdraw thread");
            return 1;
        }
    }
    for (int i = 0; i < dN; i++) 
    {
        if (pthread_join(deposit_threads[i], NULL) != 0) 
        {
            perror("Failed to join deposit thread");
            return 1;
        }
    }
    for (int i = 0; i < wN; i++) 
    {
        if (pthread_join(withdraw_threads[i], NULL) != 0) 
        {
            perror("Failed to join withdraw thread");
            return 1;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time taken: %f seconds\n", cpu_time_used);
    printf("Final balance: %lld\n", balance);
    
    #if USE_MUTEX
        pthread_mutex_destroy(&mutex);
    #elif USE_SPINLOCK
        pthread_spin_destroy(&spinLock);
    #endif

    return 0;

}