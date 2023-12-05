/**
*@description:类嵌套
*@author:nifei
*@date:2023-12-05
**/

#include <iostream>

class Animal{
    public:
    Animal(){
        std::cout << "Animal() is called" << std::endl;
    }

    Animal(const Animal &) {
        std::cout << "Animal (const Animal &) is called" << std::endl;
    }

    Animal &operator= (const Animal &) {
        std::cout << "Animal & operator= (const Animal &) is called" << std::endl;
        return *this;
    }

    ~Animal() {
        std::cout << "~Animal() is called" << std::endl;
    }
};

class Dog {
    public:
    //第一种使用初始化列表
    // Dog(const Animal &animal) : _animal(animal) {
    //     std::cout << "Dog(const Animal &animal) is called" << std::endl;
    // }
    
    //第二种使用构造函数赋值来初始化对象
    Dog(const Animal &animal) {
        _animal = animal;
        std::cout << "Dog(const Animal &animal) is called" <<std::endl;
    }

    ~Dog(){
        std::cout << "~Dog() is called" << std::endl;
    }

    private:
    Animal _animal;
};

int main()
{
    Animal animal;
    std::cout << std::endl;
    Dog dog(animal);
    std::cout << std::endl;

    return 0;
}