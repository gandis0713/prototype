#include <iostream>
#include <set>
#include <string>


using namespace std;

class A
{
  int value;
  std::string name;
public:
  bool operator<(const A& rhs) const 
  {
    return this->value < rhs.value;
  }
};

class ACmp
{
public:
  bool operator()(const A& lhs, const A& rhs) const
  {
    std::cout << "test " << std::endl;
    return false;
  }
};


int main() 
{
  std::set<A, ACmp> data;

  A a;
  data.insert(a);

  return 0;
}