#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


//todo  存在异常问题

typedef struct
{
    void (*function)(void *); // 任务函数
    void *data;               // 任务数据
} Task;

typedef struct
{
    Task *taskQueue;            // 任务队列
    size_t queueSize;           // 队列大小
    size_t front;               // 队头
    size_t rear;                // 队尾
    pthread_mutex_t queueMutex; // 队列互斥锁
    pthread_cond_t queueCond;   // 队列条件变量
    pthread_t *threads;         // 线程数组
    size_t numThreads;          // 线程数量
    int shutdown;               // 线程池关闭标志
} ThreadPool;

void *worker(void *threadPool);

// 初始化线程池
ThreadPool *threadPoolCreate(size_t numThreads, size_t queueSize)
{
    ThreadPool *pool = (ThreadPool *)malloc(sizeof(ThreadPool));
    if (pool == NULL)
    {
        perror("Failed to create thread pool");
        return NULL;
    }
    pool->taskQueue = (Task *)malloc(sizeof(Task) * queueSize);
    if (pool->taskQueue == NULL)
    {
        perror("Failed to create task queue");
        free(pool);
        return NULL;
    }
    pool->queueSize = queueSize;
    pool->front = pool->rear = 0;
    pthread_mutex_init(&(pool->queueMutex), NULL);
    pthread_cond_init(&(pool->queueCond), NULL);
    pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * numThreads);
    pool->numThreads = numThreads;
    pool->shutdown = 0;

    for (size_t i = 0; i < numThreads; i++)
    {
        if (pthread_create(&(pool->threads[i]), NULL, worker, (void *)pool) != 0)
        {
            perror("Failed to create thread");
            free(pool->taskQueue);
            free(pool);
            return NULL;
        }
    }
    return pool;
}

// 添加任务到线程池
int threadPoolAddTask(ThreadPool *pool, void (*function)(void *), void *data)
{
    // // sleep(1);
    // pthread_mutex_lock(&(pool->queueMutex));
    // if (pool->rear == pool->queueSize)
    // {
    //     pthread_mutex_unlock(&(pool->queueMutex));
    //     printf("Task queue full");
    //     return -1; // 队列已满
    // }
    // pool->taskQueue[pool->rear].function = function;
    // pool->taskQueue[pool->rear].data = data;
    // pool->rear = (pool->rear + 1) % pool->queueSize;
    // pthread_cond_signal(&(pool->queueCond));
    // pthread_mutex_unlock(&(pool->queueMutex));
    // return 0;
    usleep(10000);
    int attempts = 0;
    while (attempts < 5)
    {
        // printf("task add attempts:%d", attempts);
        pthread_mutex_lock(&(pool->queueMutex));
        if (pool->rear != pool->queueSize)
        {
            pool->taskQueue[pool->rear].function = function;
            pool->taskQueue[pool->rear].data = data;
            pool->rear = (pool->rear + 1) % pool->queueSize;
            pthread_cond_signal(&(pool->queueCond));
            pthread_mutex_unlock(&(pool->queueMutex));
            return 0;
        }
        printf("task add attempts:%d", attempts);

        pthread_mutex_unlock(&(pool->queueMutex));
        usleep(10000); // Sleep for 10 milliseconds (adjust as needed)
        attempts++;
    }
    return -1; // Failed after maxAttempts
}

// 销毁线程池
void threadPoolDestroy(ThreadPool *pool)
{
    if (pool == NULL)
        return;
    pool->shutdown = 1;
    pthread_cond_broadcast(&(pool->queueCond));
    for (size_t i = 0; i < pool->numThreads; i++)
    {
        pthread_join(pool->threads[i], NULL);
    }
    free(pool->threads);
    free(pool->taskQueue);
    free(pool);
}

void *worker(void *threadPool)
{
    ThreadPool *pool = (ThreadPool *)threadPool;
    while (1)
    {
        pthread_mutex_lock(&(pool->queueMutex));
        printf("pool->front:%d pool->rear:%d\n", pool->front, pool->rear);
        while (!pool->shutdown && pool->front == pool->rear)
        {
            pthread_cond_wait(&(pool->queueCond), &(pool->queueMutex));
        }
        if (pool->shutdown)
        {
            pthread_mutex_unlock(&(pool->queueMutex));
            pthread_exit(NULL);
        }
        Task task = pool->taskQueue[pool->front];
        pool->front = (pool->front + 1) % pool->queueSize;
        pthread_mutex_unlock(&(pool->queueMutex));
        printf("task run");
        task.function(task.data);
    }
    pthread_exit(NULL);
}

void taskFunction(void *data)
{
    // 执行任务的代码
    int *arg = (int *)data;
    printf("Task result: %d\n", arg[0] + arg[1]);
}

void taskAdd(void *data)
{
    int *arg = (int *)data;
    printf("Task add result: %d\n", arg[0] + arg[1]);
}

void *taskAdder(void *threadPool)
{
    ThreadPool *pool = (ThreadPool *)threadPool;

    int args1[] = {1, 2};
    int args2[] = {10, 3};

    for (int i = 0; i < 10; i++)
    {
        args1[1] = i;
        threadPoolAddTask(pool, taskFunction, args1);
                // 唤醒一个工作线程
        pthread_mutex_lock(&(pool->queueMutex));
        pthread_cond_signal(&(pool->queueCond));
        pthread_mutex_unlock(&(pool->queueMutex));
        
        threadPoolAddTask(pool, taskAdd, args2);

        // 唤醒一个工作线程
        pthread_mutex_lock(&(pool->queueMutex));
        pthread_cond_signal(&(pool->queueCond));
        pthread_mutex_unlock(&(pool->queueMutex));

    }

    return NULL;
}

int main()
{
    ThreadPool *pool = threadPoolCreate(1, 2);

    pthread_t adderThread;
    if (0 != pthread_create(&adderThread, NULL, taskAdder, pool))
    {
        perror("Failed to create task adder thread");
        exit(EXIT_FAILURE);
    }

    pthread_join(adderThread, NULL);

    sleep(5); // 等待任务执行完成

    threadPoolDestroy(pool);

    return 0;
}
