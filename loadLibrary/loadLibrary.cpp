#include <iostream>
// #include <filesystem>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <dlfcn.h>
#endif

int main() {
    // 定义动态库名称 libadd  or  add s
    const char* libraryName = "libadd";

    // std::filesystem::path currentPath = std::filesystem::current_path();
    // std::cout << "Current working directory: " << currentPath << std::endl;

    // 加载动态库
#if defined(_WIN32) || defined(_WIN64)
    HINSTANCE libraryHandle = LoadLibraryA(libraryName);
    if (!libraryHandle) {
        std::cerr << "Failed to load library: " << GetLastError() << std::endl;
        return 1;
    }

    char buffer[MAX_PATH];
    DWORD result = GetCurrentDirectory(MAX_PATH, buffer);
    if (result != 0 && result < MAX_PATH) {
        std::cout << "Current working directory: " << buffer << std::endl;
    } else {
        DWORD error = GetLastError();
        std::cerr << "Error getting current directory. Error code: " << error << std::endl;
    }

#else
    void* libraryHandle = dlopen(libraryName, RTLD_LAZY);
    if (!libraryHandle) {
        std::cerr << "Failed to load library: " << dlerror() << std::endl;
        return 1;
    }

    char buffer[PATH_MAX];
    if (getcwd(buffer, sizeof(buffer)) != nullptr) {
        std::cout << "Current working directory: " << buffer << std::endl;
    } else {
        perror("getcwd");
    }

#endif

    // 获取动态库中的函数指针
    typedef void (*MyFunctionType)();

    typedef int (*AddFunctionType)(int, int);
    AddFunctionType myFunction;

#if defined(_WIN32) || defined(_WIN64)
    myFunction = (AddFunctionType)GetProcAddress(libraryHandle, "add");
#else
    myFunction = (AddFunctionType)dlsym(libraryHandle, "add");
#endif
    if (!myFunction) {
        std::cerr << "Failed to get function pointer" << std::endl;
        return 1;
    }

    // 调用动态库中的函数
    std::cout << myFunction(1, 2) << std::endl;

    // 卸载动态库
#if defined(_WIN32) || defined(_WIN64)
    FreeLibrary(libraryHandle);
#else
    dlclose(libraryHandle);
#endif

    return 0;
}
