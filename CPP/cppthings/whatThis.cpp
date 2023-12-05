/**
 *@description:this 是什么东西
 *@author:nifei
 *@date:2023-12-05
 **/

#include <iostream>

class MyClass
{
public:
    void printAddress()
    {
        std::cout << "Address of the current object this: " << this << std::endl;
    }

    void printMemberValue()
    {
        std::cout << "member value of the current object: " << _member << std::endl;
    }

private:
    int _member = 1024;
};

int main()
{
    MyClass obj;

    obj.printAddress();
    obj.printMemberValue();

    std::cout << "obj Address is: " << &obj << std::endl;

    return 0;
}