// #ifdef _WIN32
// // Windows 版本
// #include <Windows.h>

// class NamedMutex {
// public:
//     NamedMutex(const char* name) {
//         mutex_ = CreateMutexA(NULL, FALSE, name);
//     }

//     ~NamedMutex() {
//         if (mutex_ != NULL) {
//             CloseHandle(mutex_);
//         }
//     }

//     bool Lock() {
//         if (mutex_ == NULL) {
//             return false;
//         }

//         DWORD result = WaitForSingleObject(mutex_, INFINITE);
//         return (result == WAIT_OBJECT_0);
//     }

//     void Unlock() {
//         if (mutex_ != NULL) {
//             ReleaseMutex(mutex_);
//         }
//     }

// private:
//     HANDLE mutex_;
// };

// #else
// // Linux 版本
// #include <fcntl.h>
// #include <sys/stat.h>
// #include <sys/types.h>
// #include <unistd.h>

// class NamedMutex {
// public:
//     NamedMutex(const char* name) {
//         mutex_ = open(name, O_CREAT, S_IRUSR | S_IWUSR);
//     }

//     ~NamedMutex() {
//         if (mutex_ != -1) {
//             close(mutex_);
//             unlink(name_);
//         }
//     }

//     bool Lock() {
//         if (mutex_ == -1) {
//             return false;
//         }

//         struct flock fl;
//         fl.l_type = F_WRLCK;
//         fl.l_whence = SEEK_SET;
//         fl.l_start = 0;
//         fl.l_len = 0;

//         int result = fcntl(mutex_, F_SETLKW, &fl);
//         return (result != -1);
//     }

//     void Unlock() {
//         if (mutex_ != -1) {
//             struct flock fl;
//             fl.l_type = F_UNLCK;
//             fl.l_whence = SEEK_SET;
//             fl.l_start = 0;
//             fl.l_len = 0;

//             fcntl(mutex_, F_SETLK, &fl);
//         }
//     }

// private:
//     int mutex_;
// };

// #endif

int main() {
    // NamedMutex mutex("my_named_mutex");

    // // 在多进程环境中使用命名互斥锁保护临界区
    // if (mutex.Lock()) {
    //     printf("Critical section protected by named mutex.\n");
    //     mutex.Unlock();
    // }

    return 0;
}
