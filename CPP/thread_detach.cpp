#include <iostream>
#include <thread>
#include <csignal>
#include <atomic>

#include <fstream>

// 使用 atomic 标志来通知线程退出
std::atomic<bool> stopFlag(false);

// 信号处理程序，用于捕获 Ctrl+C 信号
void signalHandler(int signal) {
    if (signal == SIGINT) {
        std::cout << "Ctrl+C detected. Stopping threads..." << std::endl;
        stopFlag.store(true); // 设置停止标志
    }
}

// 你的线程函数
void workerThread() {
    
    std::cout << "Thread running..." << std::endl;
    std::cout << "worker thread:" << getpid() << std::endl;
    while (!stopFlag.load()) {
        // 执行线程工作
        // ...
        
    std::string filename = "threadDetachTest.txt";
    std::ofstream outputFile;

    outputFile.open(filename, std::ios::app);

    if (!outputFile.is_open())
    {
        std::cerr << "can not open file " << filename << std::endl;
        return;
    }

    outputFile << "threadDetach write file success\n";

    outputFile.close();

    std::cout << "worker thread:" << getpid() << std::endl;
    }
    std::cout << "Thread exiting..." << std::endl;
}

int main() {
    // 注册信号处理程序
    signal(SIGINT, signalHandler);

    // 创建并启动线程
    std::thread worker(workerThread);
    
    std::cout << "main thread:" << getpid() << std::endl;
    // worker.join();
    worker.detach();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Main thread exiting..." << std::endl;
    return 0;
}