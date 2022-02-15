#include <iostream>
#include <cstring>
#include <chrono>

int main()
{
  size_t size = 30000;
  size_t s = 0;

  int *pData = new int[size];
  memset(pData, 0, size);

  std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      s += pData[j];
    }
  }

  std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;

  std::cout << "time : " << sec.count() << " seconds" << std::endl;

  s = 0;
  start = std::chrono::system_clock::now();
  for (int j = 0; j < size; j++) {
    for (int i = 0; i < size; i++) {
      s += pData[j];
    }
  }
  sec = std::chrono::system_clock::now() - start;
  std::cout << "time : " << sec.count() << " seconds" << std::endl;

  return 0;
}