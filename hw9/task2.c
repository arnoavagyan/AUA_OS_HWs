#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int* arr;
    int start;
    int end;
} ThreadData;

void* arraySum(void* arg)
{
    ThreadData* data = (ThreadData*)arg;
    int sum = 0;

    for (int i = data->start; i < data->end; i++) {
        sum += data->arr[i];
    }

    int* result = malloc(sizeof(int));
    *result = sum;
    return result;
}

int main()
{
    pthread_t thread1, thread2;

    // int arr[] = {1, 2, 3, 4, 5, 6, 7, 8}; // even size
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // odd size

    int size = sizeof(arr) / sizeof(arr[0]);

    ThreadData d1 = {arr, 0, size/2};
    ThreadData d2 = {arr, size/2, size};

    if (pthread_create(&thread1, NULL, arraySum, &d1) != 0) {
        perror("Failed to create thread 1");
        return 1;
    }
    if (pthread_create(&thread2, NULL, arraySum, &d2) != 0) {
        perror("Failed to create thread 2");
        return 1;
    }

    int *sum1, *sum2;
    if (pthread_join(thread1, (void**)&sum1) != 0) {
        perror("Failed to join thread 1");
        return 1;
    }
    if (pthread_join(thread2, (void**)&sum2) != 0) {
        perror("Failed to join thread 2");
        return 1;
    }
    printf("Sum of array part 1: %d\n", *sum1);
    printf("Sum of array part 2: %d\n", *sum2);

    return 0;
}