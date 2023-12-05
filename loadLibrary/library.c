#include<stdio.h>

#ifdef WIN32
#define EXPORT __declspec(dllexport)
#else
// use -fvisibility=hidden to change the "default" behavior
#define EXPORT __attribute__((visibility("default")))
#endif

EXPORT int add (int a, int b)
{
    return a + b;
}