#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>

typedef struct
{
    int data;
    bool valid; // 表示资源是否有效
} Resource;

typedef uint32_t Handle;

typedef struct
{
    Handle handle;
    Resource *resource;
} HandleEntry;

#define MAX_HANDLE_ENTRIES 1000

HandleEntry g_handleTable[MAX_HANDLE_ENTRIES] = {0};
pthread_mutex_t g_handleTableMutex; // 用于保护句柄表的互斥锁

uint32_t hash(Handle handle)
{
    return handle % MAX_HANDLE_ENTRIES;
}

void initHandleTable()
{
    memset(g_handleTable, 0, sizeof(g_handleTable));
    pthread_mutex_init(&g_handleTableMutex, NULL);
}

Resource *findResource(Handle handle)
{
    pthread_mutex_lock(&g_handleTableMutex);
    uint32_t idx = hash(handle);
    while (g_handleTable[idx].handle != 0)
    {
        if (g_handleTable[idx].handle == handle)
        {
            Resource *resource = g_handleTable[idx].resource;
            if (resource->valid)
            {
                pthread_mutex_unlock(&g_handleTableMutex);
                return resource;
            }
            else
            {
                // 资源无效，句柄已失效
                pthread_mutex_unlock(&g_handleTableMutex);
                return NULL;
            }
        }
        idx = (idx + 1) % MAX_HANDLE_ENTRIES;
    }
    pthread_mutex_unlock(&g_handleTableMutex);
    return NULL;
}

bool insertHandle(Handle handle, Resource *resource)
{
    pthread_mutex_lock(&g_handleTableMutex);
    uint32_t idx = hash(handle);
    while (g_handleTable[idx].handle != 0)
    {
        if (g_handleTable[idx].handle == handle)
        {
            // 句柄已存在，不允许重复插入
            pthread_mutex_unlock(&g_handleTableMutex);
            return false;
        }
        idx = (idx + 1) % MAX_HANDLE_ENTRIES;
    }

    // 找到空闲位置，插入新的映射关系
    g_handleTable[idx].handle = handle;
    g_handleTable[idx].resource = resource;
    pthread_mutex_unlock(&g_handleTableMutex);
    return true;
}

bool removeHandle(Handle handle)
{
    pthread_mutex_lock(&g_handleTableMutex);
    uint32_t idx = hash(handle);
    while (g_handleTable[idx].handle != 0)
    {
        if (g_handleTable[idx].handle == handle)
        {
            // 找到句柄，将映射关系删除
            g_handleTable[idx].handle = 0;
            Resource *resource = g_handleTable[idx].resource;
            resource->valid = false; // 将资源标记为无效
            pthread_mutex_unlock(&g_handleTableMutex);
            return true;
        }
        idx = (idx + 1) % MAX_HANDLE_ENTRIES;
    }
    pthread_mutex_unlock(&g_handleTableMutex);
    return false;
}

// 创建资源对象
Resource *createResource(int data)
{
    Resource *resource = (Resource *)malloc(sizeof(Resource));
    if (resource != NULL)
    {
        resource->data = data;
        resource->valid = true;
    }
    return resource;
}

// 销毁资源对象
void destroyResource(Resource *resource)
{
    if (resource != NULL)
    {
        free(resource);
    }
}

void resourceOperation(Handle handle)
{
    Resource *resource = findResource(handle);
    if (resource != NULL)
    {
        printf("Resource data: %d\n", resource->data);
    }
    else
    {
        printf("Invalid handle or resource not found.\n");
    }
}

int main()
{
    initHandleTable();

    Resource *resource1 = createResource(123);
    Handle handle1 = 1;
    insertHandle(handle1, resource1);

    Resource *resource2 = createResource(456);
    Handle handle2 = 2;
    insertHandle(handle2, resource2);

    resourceOperation(handle1);
    resourceOperation(handle2);

    removeHandle(handle1);
    removeHandle(handle2);

    // 销毁资源对象
    destroyResource(resource1);
    destroyResource(resource2);

    // 销毁互斥锁
    pthread_mutex_destroy(&g_handleTableMutex);

    return 0;
}
