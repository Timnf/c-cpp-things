#include <iostream>
#include <functional>
#include <thread>
#include <chrono>

class AsyncSDK {
public:
    using AsyncCallback = std::function<void(int)>;

    void startAsyncOperation(int input, AsyncCallback callback) {
        // 模拟异步操作
        std::thread([this, input, callback]() {
            std::this_thread::sleep_for(std::chrono::seconds(2)); // 模拟操作耗时
            int result = input * 2;

            // 调用回调函数，传递结果给上层应用
            callback(result);
        }).detach();
    }
};

int main() {
    AsyncSDK asyncSDK;

    asyncSDK.startAsyncOperation(5, [](int result) {
        std::cout << "Async operation completed. Result: " << result << std::endl;
    });

    std::cout << "Waiting for async operation to complete..." << std::endl;

    // 等待异步操作完成
    std::this_thread::sleep_for(std::chrono::seconds(3));

    return 0;
}
