#include <iostream>

class A
{
public:
  A() = default;
  A(const A& rhs) = default;
  A(int v) {};
};

int main()
{
  std::cout << "default" << std::endl;

  A a1;
  A a2 = a1;

  return 0;
}