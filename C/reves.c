#include <stdio.h>

void reverseByteArray(unsigned char *arr, size_t size) {
    unsigned char temp;
    size_t start = 0;
    size_t end = size - 1;
    
    while (start < end) {
        // Swap elements
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        
        // Move to the next pair
        start++;
        end--;
    }
}

int main() {
    // Example usage
    unsigned char byteArray[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    size_t size = sizeof(byteArray) / sizeof(byteArray[0]);
    
    printf("Original Array: ");
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", byteArray[i]);
    }
    printf("\n");
    
    reverseByteArray(byteArray, size);
    
    printf("Reversed Array: ");
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", byteArray[i]);
    }
    printf("\n");
    
    return 0;
}
