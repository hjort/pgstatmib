#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* thread1()
{
        while(1) {
                printf("Thread1\n");
		sleep(1);
        }
}

void* thread2()
{
        while(1) {
                printf("Thread2\n");
		sleep(5);
        }
}

int main()
{
        int status;
        pthread_t tid1, tid2;

        pthread_create(&tid1, NULL, &thread1, NULL);
        pthread_create(&tid2, NULL, &thread2, NULL);

        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

        return 0;
}
