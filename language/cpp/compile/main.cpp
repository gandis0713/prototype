#include <iostream>
#include <string>
#include <thread>

thread_local int thread_value;
int g_value;

void test_function();
int main()
{
  std::thread thr1(test_function);
  std::thread thr2(test_function);
  thr1.join();
  thr2.join();
  return 0;
}

void test_function()
{
  std::cout << "thread : " << ++thread_value << std::endl;
  std::cout << "global : " << ++g_value << std::endl;
}