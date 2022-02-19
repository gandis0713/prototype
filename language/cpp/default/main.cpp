#include <iostream>

class A
{
public:
  A() = default;
  A(const A& rhs) = default;
  A& operator=(const A& rhs) = default;
  // A& operator=(const A& rhs)
  // {
  //   std::cout << "operator copy" << std::endl;
  //   return *this;
  // }

  int v;
};



int main()
{

  A a1;
  A a2 = a1;
  a2.v = 10;
  A a3;
  a3 = a2;
  std::cout << "a3 : " << a3.v << std::endl;
  std::cout << "a2 : " << a2.v << std::endl;

  return 0;
}