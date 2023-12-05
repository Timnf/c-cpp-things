#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int i, j, k;
    int n = 500; // 抽取球的次数
    int N = 1100; // 球的总数
    int M = 100; // 红球的数量
    int K = 44; // 抽到红球的数量
    int count = 0;
    double p;

    srand((unsigned)time(NULL));

    for (i = 0; i < 500; i++)
    {
        int red = 0;
        for (j = 0; j < n; j++)
        {
            if (rand() % N < M)
            {
                red++;
            }
        }
        if (red == K)
        {
            count++;
        }
    }

    // p = (double)count / 1000000;
    p = (double)count;

    printf("P(X=%d)=%f\n", K, p);

    return 0;
}
