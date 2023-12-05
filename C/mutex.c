#include <stdio.h>

#ifdef _WIN32
// Windows 版本
#include <Windows.h>

typedef struct {
    CRITICAL_SECTION mutex;
} Mutex;

void mutex_init(Mutex* mutex) {
    InitializeCriticalSection(&mutex->mutex);
}

void mutex_destroy(Mutex* mutex) {
    DeleteCriticalSection(&mutex->mutex);
}

void mutex_lock(Mutex* mutex) {
    EnterCriticalSection(&mutex->mutex);
}

void mutex_unlock(Mutex* mutex) {
    LeaveCriticalSection(&mutex->mutex);
}

#else
// Linux 版本
#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex;
} Mutex;

void mutex_init(Mutex* mutex) {
    pthread_mutex_init(&mutex->mutex, NULL);
}

void mutex_destroy(Mutex* mutex) {
    pthread_mutex_destroy(&mutex->mutex);
}

void mutex_lock(Mutex* mutex) {
    pthread_mutex_lock(&mutex->mutex);
}

void mutex_unlock(Mutex* mutex) {
    pthread_mutex_unlock(&mutex->mutex);
}

#endif

#ifdef _WIN32
DWORD WINAPI thread_func(LPVOID lpParam) {
    Mutex* mutex = (Mutex*)lpParam;

    // 循环多次访问临界区
    for (int i = 0; i < 5; i++) {
        mutex_lock(mutex);
        printf("Thread %u entered critical section.\n", GetCurrentThreadId());
        Sleep(1000); // 模拟临界区的操作
        printf("Thread %u exited critical section.\n", GetCurrentThreadId());
        mutex_unlock(mutex);
    }

    return 0;
}

#else
// Linux 版本
#include <pthread.h>

void* thread_func(void* arg) {
    Mutex* mutex = (Mutex*)arg;

    // 循环多次访问临界区
    for (int i = 0; i < 5; i++) {
        mutex_lock(mutex);
        printf("Thread %ld entered critical section.\n", pthread_self());
        usleep(1000000); // 模拟临界区的操作，单位为微秒
        printf("Thread %ld exited critical section.\n", pthread_self());
        mutex_unlock(mutex);
    }

    return NULL;
}

#endif

int main() {
    Mutex mutex;
    mutex_init(&mutex);

#ifdef _WIN32
    // Windows 版本
    HANDLE threadHandles[3];
    DWORD threadIds[3];

    // 创建多个线程
    for (int i = 0; i < 3; i++) {
        threadHandles[i] = CreateThread(NULL, 0, thread_func, &mutex, 0, &threadIds[i]);
        if (threadHandles[i] == NULL) {
            printf("Failed to create thread %d.\n", i);
            return 1;
        }
    }

    // 等待所有线程结束
    WaitForMultipleObjects(3, threadHandles, TRUE, INFINITE);

    // 关闭线程句柄
    for (int i = 0; i < 3; i++) {
        CloseHandle(threadHandles[i]);
    }

#else
    // Linux 版本
    pthread_t threads[3];

    // 创建多个线程
    for (int i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, thread_func, &mutex) != 0) {
            printf("Failed to create thread %d.\n", i);
            return 1;
        }
    }

    // 等待所有线程结束
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

#endif

    mutex_destroy(&mutex);

    return 0;
}
