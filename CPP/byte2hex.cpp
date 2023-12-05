#include <iostream>
#include <iomanip>
#include <sstream>

std::string BytesToHexString(const unsigned char *pData, size_t len)
{
    std::string result;
    // char szBuf[20];
    std::stringstream ss;
    for (int i = 0; i < len; i++)
    {
        // sprintf(szBuf, "%02X", pData[i]);
        // result += szBuf;
        ss.str("");
        // ss << std::hex << std::setw(2) << std::setfill('0') << pData[i];
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(pData[i]);
        result += ss.str();

    }
    return result;
}

int main()
{
    std::stringstream ss;
    std::string result = ss.str();
    std::string pData = "123456";

    result = BytesToHexString(reinterpret_cast<const unsigned char*>(pData.c_str()), pData.length());

    std::cout << "Value in hex: " << result << std::endl;

    return 0;
}
