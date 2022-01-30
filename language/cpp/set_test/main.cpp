#include <iostream>
#include <set>
#include <string>
// #include <hash>
#include <unordered_set>


using namespace std;

class ACmp;
class A
{
  int value;
  std::string name;
public:
  // bool operator<(const A& rhs) const 
  // {
  //   return this->value < rhs.value;
  // }
  bool operator==(const A& rhs) const 
  {
    std::cout << "test1 " << std::endl;
    return this->value == rhs.value;
  }

  friend class std::hash<A>;
};

namespace std
{

template<>
class hash<A>
{
public:
  size_t operator()(const A& rhs) const
  {
    std::hash<std::string> hash_func;
    std::cout << "test " << std::endl;
    return rhs.value ^ hash_func(rhs.name);
  }
};

}



int main() 
{
  // std::set<A, ACmp> data;
  std::unordered_set<A> data_unrodered;

  A a;
  A a1;
  // data.insert(a);

  data_unrodered.insert(a);
  data_unrodered.insert(a1);

  return 0;
}