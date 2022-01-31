#include <cctype>
#include <iostream>
#include <string>


int main()
{
  // std::u32string u32_str = U"UTF-32 문자열.";
  std::string u8_str = u8"UTF-32 문자열.";

  // std::cout << u32_str.size() << std::endl;
  std::cout << u8_str.size() << std::endl;
  std::cout << u8_str << std::endl;

  for(size_t i = 0; i < u8_str.size(); ++i)
  {
    std::cout << u8_str[i] << std::endl;
    unsigned char flags = u8_str[i];
    for (size_t j = 0; j < 8; ++j)
        std::cout << ((flags >> j) & 0x1);

    std::cout << '\n';

  }

  size_t i = 0;
  size_t len = 0;

  while (i < u8_str.size()) {
    int char_size = 0;

    if ((u8_str[i] & 0b11111000) == 0b11110000) {
      char_size = 4;
    } else if ((u8_str[i] & 0b11110000) == 0b11100000) {
      char_size = 3;
    } else if ((u8_str[i] & 0b11100000) == 0b11000000) {
      char_size = 2;
    } else if ((u8_str[i] & 0b10000000) == 0b00000000) {
      char_size = 1;
    } else {
      std::cout << "이상한 문자 발견!" << std::endl;
      char_size = 1;
    }

    std::cout << u8_str.substr(i, char_size) << std::endl;

    i += char_size;
    len++;
  }
  std::cout << "문자열의 실제 길이 : " << len << std::endl;






  return 0;
}