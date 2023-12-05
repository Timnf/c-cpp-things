#include <iostream>
#include <future>
#include <stdlib.h>

int asyncFunction() {
    // 在这里执行异步任务
    // _sleep(1000);
    return 42;
}

int main() {
    std::future<int> result = std::async(std::launch::async, asyncFunction);  // 异步执行函数
    std::cout << "Main thread continues." << std::endl;
    int asyncResult = result.get();  // 获取异步任务的结果
    std::cout << "Async task result: " << asyncResult << std::endl;
    return 0;
}
