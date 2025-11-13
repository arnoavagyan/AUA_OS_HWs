#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct {
    int  number;
    int* square;
} ThreadArgs;

void* square(void* arg)
{
    ThreadArgs* data = (ThreadArgs*)arg;
    int num = data->number;
    *(data->square) = num * num;
}

int main()
{
    int arr[5];
    for (int i = 0; i < 5; i++) 
    {
        arr[i] = i + 1;
    }
    for (int i = 0; i < 5; ++i)
    {
        int res;
        ThreadArgs args = { arr[i], &res };

        pthread_t t;
        if (pthread_create(&t, NULL, square, &args) != 0) 
        {
            perror("Failed to create thread");
            exit(1);
        }
        if (pthread_join(t, NULL) != 0) 
        {
            perror("Failed to join thread");
            exit(1);
        }
        printf("Square of %d is %d\n", arr[i], res);
    }
}