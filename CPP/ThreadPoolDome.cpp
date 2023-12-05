#include <iostream>
#include <vector>
#include <chrono>

#include <ThreadPool.h>

int work(int i)
{
    std::cout << "hello" << i << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "world" << i << std::endl;
    return i * i;
}

int main()
{
    ThreadPool pool(2);
    std::vector<std::future<int>> results;

    for (int i = 0; i < 2; ++i)
    {
        results.emplace_back(
            // pool.enqueue([i]{
            //     std::cout << "hello" << i << std::endl;
            //     std::this_thread::sleep_for(std::chrono::seconds(2));
            //     std::cout << "world" << i <<std::endl;
            //     return i*i;
            // })
            pool.enqueue(work, i));
    }

    for (auto &&result : results)
    {
        std::cout << "result" << result.get() << std::endl;
    }
    std::cout << std::endl;

    return 0;
}