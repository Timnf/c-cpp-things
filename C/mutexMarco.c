#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>

typedef HANDLE MutexHandle;

#define MUTEX_INIT(mutex) mutex = CreateMutex(NULL, FALSE, NULL)
#define MUTEX_LOCK(mutex) WaitForSingleObject(mutex, INFINITE)
#define MUTEX_UNLOCK(mutex) ReleaseMutex(mutex)
#define MUTEX_DESTROY(mutex) CloseHandle(mutex)

#else
#include <pthread.h>

typedef pthread_mutex_t MutexHandle;

#define MUTEX_INIT(mutex) pthread_mutex_init(&mutex, NULL)
#define MUTEX_LOCK(mutex) pthread_mutex_lock(&mutex)
#define MUTEX_UNLOCK(mutex) pthread_mutex_unlock(&mutex)
#define MUTEX_DESTROY(mutex) pthread_mutex_destroy(&mutex)

#endif

int main() {
    MutexHandle mutex;
    MUTEX_INIT(mutex);

    // 使用互斥锁保护临界区
    MUTEX_LOCK(mutex);
    printf("Critical section protected by mutex.\n");
    MUTEX_UNLOCK(mutex);

    MUTEX_DESTROY(mutex);

    return 0;
}
