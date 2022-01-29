#include <iostream>
#include <string>

class A {
 public:
  int a = 0;

  A() { std::cout << "A 생성자 호출" << std::endl; }
};

class AB : public A {
 public:
  int b = 0;

  AB() { std::cout << "AB 생성자 호출" << std::endl; }
};

class AC : public A {
 public:
  int b = 0;

  AC() { std::cout << "AC 생성자 호출" << std::endl; }
};

class D : public AB, public AC {
 public:
  int c;

  D() : AB(), AC() { std::cout << "C 생성자 호출" << std::endl; }
};

int main() 
{
    D a;
    std::cout << a.a << std::endl;
    return 0;
}
