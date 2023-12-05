#include <stddef.h> // 包含 NULL 和 size_t

// 跨平台字符串安全拷贝函数
void str_copy(char* dest, const char* src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return;
    }

    // 在不超过目标大小的情况下拷贝字符串
    size_t i;
    for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }

    // 确保目标字符串以 '\0' 结尾
    dest[i] = '\0';
}

#include <stdio.h>

int main() {
    char dest[20]; // 目标字符串缓冲区
    const char* src = "Hello, world!"; // 源字符串

    str_copy(dest, src, sizeof(dest));

    printf("Copied string: %s\n", dest);

    return 0;
}
