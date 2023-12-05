#include <stdio.h>

typedef struct stDataStruct 
{
    int iSize;
    int i[];
}STDATASTRUCT;

int main()
{
    int testSpace = sizeof(STDATASTRUCT);
    printf("testSpace:%d", testSpace);
    return 0;
}