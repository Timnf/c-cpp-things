#include <stdio.h>

int main(){
    printf("Hello, from cBase!\n");
    double d = 10000.1111111111111111;
    double d2 = d + 0.0000000000000001;
    int index = 100;

    while(index--)
    {
        if (d2 == d)
        {
            printf("index:%d:double %.20lf == double2 %.20lf\n", index, d, d2);
        }
        else
        {
            printf("index:%d:double %.20lf != double2 %.20lf\n", index, d, d2);
        }
    }
    return 0;
}
