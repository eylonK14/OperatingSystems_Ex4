// File: lab4/race.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 20

pthread_mutex_t lock;

long accum = 0;

void *square(void *param)
{
    int x = *(int *)param;
    // problem #2 - using accum causes race conditions in threads, locking the assingment to accum
    pthread_mutex_lock(&lock);
    int temp = accum;
    pthread_mutex_unlock(&lock);
    temp += x * x;
    pthread_mutex_lock(&lock);
    accum = temp;
    pthread_mutex_unlock(&lock);
    // sleep(1);
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int *params[NUM_THREADS];

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init has failed\n");
        return 1;
    }

    for (long t = 0; t < NUM_THREADS; t++)
    {
        params[t] = /*problem #1 - casting*/ (int *)malloc(sizeof(int));
        *params[t] = t + 1;
        pthread_create(&threads[t], NULL, square, (void *)params[t]);
    }

    for (long t = 0; t < NUM_THREADS; t++)
    {
        pthread_join(threads[t], NULL);
        free(params[t]);
    }

    pthread_mutex_destroy(&lock);

    printf("%ld\n", accum);
    pthread_exit(NULL);
}