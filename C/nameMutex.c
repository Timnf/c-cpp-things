#include <stdio.h>
#ifdef _WIN32
// Windows 版本
#include <Windows.h>

typedef struct {
    HANDLE mutex;
} NamedMutex;

void named_mutex_init(NamedMutex* mutex, const char* name) {
    mutex->mutex = CreateMutexA(NULL, FALSE, name);
}

void named_mutex_destroy(NamedMutex* mutex) {
    if (mutex->mutex != NULL) {
        CloseHandle(mutex->mutex);
    }
}

int named_mutex_lock(NamedMutex* mutex) {
    if (mutex->mutex == NULL) {
        return 0;
    }

    DWORD result = WaitForSingleObject(mutex->mutex, INFINITE);
    return (result == WAIT_OBJECT_0);
}

void named_mutex_unlock(NamedMutex* mutex) {
    if (mutex->mutex != NULL) {
        ReleaseMutex(mutex->mutex);
    }
}

#else
// Linux 版本
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
    int mutex;
    char name[256];
} NamedMutex;

void named_mutex_init(NamedMutex* mutex, const char* name) {
    snprintf(mutex->name, sizeof(mutex->name), "/%s", name);
    mutex->mutex = open(mutex->name, O_CREAT, S_IRUSR | S_IWUSR);
}

void named_mutex_destroy(NamedMutex* mutex) {
    if (mutex->mutex != -1) {
        close(mutex->mutex);
        unlink(mutex->name);
    }
}

int named_mutex_lock(NamedMutex* mutex) {
    if (mutex->mutex == -1) {
        return 0;
    }

    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;

    int result = fcntl(mutex->mutex, F_SETLKW, &fl);
    return (result != -1);
}

void named_mutex_unlock(NamedMutex* mutex) {
    if (mutex->mutex != -1) {
        struct flock fl;
        fl.l_type = F_UNLCK;
        fl.l_whence = SEEK_SET;
        fl.l_start = 0;
        fl.l_len = 0;

        fcntl(mutex->mutex, F_SETLK, &fl);
    }
}

#endif

int main() {
    NamedMutex mutex;
    named_mutex_init(&mutex, "my_named_mutex");

    // 在多进程环境中使用命名互斥锁保护临界区
    if (named_mutex_lock(&mutex)) {
        printf("Critical section protected by named mutex.\n");
        named_mutex_unlock(&mutex);
    }

    named_mutex_destroy(&mutex);

    return 0;
}
