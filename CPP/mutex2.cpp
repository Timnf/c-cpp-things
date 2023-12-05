#include <iostream>

#ifdef _WIN32
// Windows 版本
#include <Windows.h>

class Mutex {
public:
    Mutex() {
        InitializeCriticalSection(&mutex_);
    }

    ~Mutex() {
        DeleteCriticalSection(&mutex_);
    }

    void lock() {
        EnterCriticalSection(&mutex_);
    }

    void unlock() {
        LeaveCriticalSection(&mutex_);
    }

private:
    CRITICAL_SECTION mutex_;
};

#else
// Linux 版本
#include <pthread.h>

class Mutex {
public:
    Mutex() {
        pthread_mutex_init(&mutex_, nullptr);
    }

    ~Mutex() {
        pthread_mutex_destroy(&mutex_);
    }

    void lock() {
        pthread_mutex_lock(&mutex_);
    }

    void unlock() {
        pthread_mutex_unlock(&mutex_);
    }

private:
    pthread_mutex_t mutex_;
};

#endif

int main() {
    Mutex mutex;
    
    // 使用互斥锁保护临界区
    mutex.lock();
    std::cout << "Critical section protected by mutex." << std::endl;
    mutex.unlock();

    return 0;
}
