#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// http://www.thegeekstuff.com/2012/05/c-mutex-examples/

void* doSomeThing(void *);

pthread_t tid[2];
int counter;

// A Mutex is a lock that we set before using a shared resource and release after using it.
// When the lock is set, no other thread can access the locked region of code.
pthread_mutex_t lock;

void* doSomeThing(void *arg)
{
    unsigned long i;

	// 2. mutex is locked while using the shared resource ‘counter’
    pthread_mutex_lock(&lock);

    i = 0;
    counter += 1;
    printf("\n Job %d started\n", counter);

    for (i=0; i<(0xFFFFFFFF); i++);

    printf("\n Job %d finished\n", counter);

	// 3. the same mutex is unlocked
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(void)
{
    int i = 0;
    int err;

	// 1. mutex is initialized
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    while (i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

	// 4. when both the threads are done, the mutex is destroyed
    pthread_mutex_destroy(&lock);

    return 0;
}

