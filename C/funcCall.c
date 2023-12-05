#include <stdio.h>

typedef void (*ctqm_volte_init_cb)(int init_result, char *p_comment);

static ctqm_volte_init_cb ctqmInitCb;

void ctqm_volte_initcb(int init_result, char *p_comment)
{
    printf("init_result:%d\np_comment:%s\n", init_result, p_comment);
}

int ctqm_volte_init(ctqm_volte_init_cb init_cb)
{
    ctqmInitCb = init_cb;
}

int main()
{
    ctqm_volte_init(ctqm_volte_initcb);
    ctqmInitCb(100, "test call back");

    return 0;
}