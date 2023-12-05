/**
*@description:类初始化定义
*@author:nifei
*@date:2023-12-05
**/

#include <iostream>

using namespace std;

class A {
    public:
    A(int a) : _a(a), _p(nullptr){

    }

    int getA(){
        return _a;
    }

    private:
        int _a;
        int *_p;
};

int main()
{
    A aa(10);
    cout << "getA: " << aa.getA() << endl;
    return 0;
}