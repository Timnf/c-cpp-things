#include <stdio.h>

#if defined(linux) || defined(__linux__)
#include <netinet/in.h>
#endif

#ifdef _WIN32
#include <WINSOCK2.H>
#pragma comment(lib, "ws2_32.lib")
#endif

// 定义宏根据大小端进行字节序转换
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define LE_TO_UINT16(ptr) ((UINT16)(ptr)[0] << 8| ((UINT16)(ptr)[1]))
#define LE_TO_UINT32(ptr) ((UINT32)(ptr)[0] << 24 | ((UINT32)(ptr)[1] << 16) | ((UINT32)(ptr)[2] << 8) | ((UINT32)(ptr)[3]))
#else
#define LE_TO_UINT16(ptr) *((UINT16 *)(ptr))
#define LE_TO_UINT32(ptr) *((UINT32 *)(ptr))
#endif

int main(void)
{
    unsigned int ultest = 0x12345678;
    unsigned short ustest = 0x1234;

    // BYTE btest[2] = {0x6a, 0x89};

    printf("ultest xiaoduan:0x%x\n", ultest);
    printf("ustest xiaoduan:0x%x\n", ustest);
    //    ultest=htonl(ultest);/*unsigned int   大小端转化 */
    // ustest = GET16(&btest[2 - 2]); /*unsigned short 大小端转化 */
                                   //    ustest= GET16(&btest[2-2]);/*unsigned short 大小端转化 */
    // ustest = GET16(&btest[2 - 2]); /*unsigned short 大小端转化 */

    UINT16 pstest = LE_TO_UINT16((BYTE*)&ustest);
    UINT32 pltest = LE_TO_UINT32((BYTE*)&ultest);

    printf("ultest daduan:0x%x\n", ultest);
    printf("ustest daduan:0x%x\n", ustest);
    printf("pstest daduan:0x%x\n", pstest);
    printf("pltest daduan:0x%x\n", pltest);
    while (1)
        ;
}