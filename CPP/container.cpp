#include <iostream>
#include <vector>
#include <list>
#include <map>

int main() {
    // 使用 vector 存储整数
    std::vector<int> intVector;
    intVector.push_back(10);
    intVector.push_back(20);
    intVector.push_back(30);

    std::cout << "Vector elements: ";
    for (const auto& num : intVector) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 使用 list 存储字符串
    std::list<std::string> stringList;
    stringList.push_back("apple");
    stringList.push_back("banana");
    stringList.push_back("cherry");

    std::cout << "List elements: ";
    for (const auto& str : stringList) {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    // 使用 map 存储姓名和年龄的关联
    std::map<std::string, int> ageMap;
    ageMap["Alice"] = 25;
    ageMap["Bob"] = 30;
    ageMap["Charlie"] = 28;

    std::cout << "Map elements (Name -> Age):" << std::endl;
    for (const auto& entry : ageMap) {
        std::cout << entry.first << " -> " << entry.second << std::endl;
    }

    return 0;
}
