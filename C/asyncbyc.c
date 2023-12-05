#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct AsyncData 
{
    int arg1;
    int arg2;
    int (*callback)(int, int);
} STASYNCDATA;

int add(int a, int b) {
    sleep(1);
    return a + b;
}

int subtract(int a, int b) {
    sleep(5);
    return a - b;
}

void *thread_async_operation(void *arg)
{
    STASYNCDATA *asyncData = (STASYNCDATA *)arg;
    int res = asyncData->callback(asyncData->arg1, asyncData->arg2);
    asyncData->arg1 = res;
    return NULL;
}

int main()
{
    STASYNCDATA asyncData1 = {0};
    STASYNCDATA asyncData2 = {0};
    
    asyncData1.arg1 = 1;
    asyncData1.arg2 = 2;
    asyncData1.callback = add;

    asyncData2.arg1 = 10;
    asyncData2.arg2 = 3;
    asyncData2.callback = subtract;

    pthread_t thread1, thread2;
    if (pthread_create(&thread1, NULL, thread_async_operation, &asyncData1) != 0 ||
        pthread_create(&thread2, NULL, thread_async_operation, &asyncData2) != 0)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Async result1: %d\n", asyncData1.arg1);
    printf("Async result2: %d\n", asyncData2.arg1);

    return 0;
}
