// #include <iostream>
// #include <unordered_map>
// #include <functional>
// #include <stdexcept>

// // 定义一个函数指针类型，用于保存不同类型的函数
// template <typename ReturnType, typename... Args>
// using FunctionPointer = ReturnType(*)(Args...);

// // 函数注册表，将函数名称映射到函数指针
// std::unordered_map<std::string, FunctionPointer<void, int, int>> functionRegistry;

// // 注册函数
// template <typename ReturnType, typename... Args>
// void RegisterFunction(const std::string& functionName, FunctionPointer<ReturnType, Args...> func) {
//     functionRegistry[functionName] = reinterpret_cast<FunctionPointer<void, int, int>>(func);
// }

// // 动态调用函数
// template <typename ReturnType, typename... Args>
// ReturnType CallFunction(const std::string& functionName, Args... args) {
//     auto it = functionRegistry.find(functionName);
//     if (it != functionRegistry.end()) {
//         FunctionPointer<void, Args...> func = it->second;
//         return reinterpret_cast<ReturnType(*)(Args...)>(func)(args...);
//     } else {
//         throw std::runtime_error("Function not found in registry.");
//     }
// }

// // 示例函数
// int Add(int a, int b) {
//     return a + b;
// }

// double Multiply(double a, double b) {
//     return a * b;
// }

int main() {
    // // 注册示例函数
    // RegisterFunction("Add", FunctionPointer<int, int, int>(Add));
    // RegisterFunction("Multiply", FunctionPointer<double, double, double>(Multiply));

    // // 动态调用函数
    // try {
    //     int result1 = CallFunction<int>("Add", 5, 3);
    //     double result2 = CallFunction<double>("Multiply", 2.5, 4.0);

    //     std::cout << "Result 1: " << result1 << std::endl;
    //     std::cout << "Result 2: " << result2 << std::endl;
    // } catch (const std::exception& e) {
    //     std::cerr << "Error: " << e.what() << std::endl;
    // }

    return 0;
}
