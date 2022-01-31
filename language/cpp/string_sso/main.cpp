#include <cctype>
#include <iostream>
#include <string>


void* operator new(size_t size)
{
  std::cout << size << " byte" << std::endl;
  return malloc(size);
}

int main()
{
  std::string strLong = "1234567890123456789012345678901"; // 32 byte
  std::string strShort = "123456789012345"; // 16 byte
  
  std::cout << sizeof(std::string) << " size" << std::endl;
  return 0;
}