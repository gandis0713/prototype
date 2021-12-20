#include <functional>
#include <iostream>
#include <string>

class A {
  int c;
  static int b;

 public:
  A(int c) : c(c) {}
  int some_func() {
    std::cout << "비상수 함수: " << ++c << std::endl;
    return c;
  }

  static int some_const_function(int a)  {
    std::cout << "상수 함수: " << a << std::endl;
    std::cout << "상수 함수: " << A::b++ << std::endl;
    return a;
  }

  static void st() {}
};

int main() {
  A a(5);
  std::function<int(A&)> f1 = &A::some_func;
  std::function<int(int)> f2 = &A::some_const_function;

  f1(a);
  f2(1);
}