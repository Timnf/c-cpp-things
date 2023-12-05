#include <iostream>
#include <thread>
#include <stdlib.h>

void asyncFunction() {
    // 在这里执行异步任务
    std::cout << "Async task is running1." << std::endl;
    // _sleep(1000);
    std::cout << "Async task is running2." << std::endl;
}

int main() {
    std::thread t(asyncFunction);  // 创建一个新线程并执行异步函数
    
    std::cout << "Main thread continues1." << std::endl;
    t.join();  // 等待线程执行完毕
    std::cout << "Main thread continues2." << std::endl;
    return 0;
}
