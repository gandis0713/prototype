#include <algorithm>
#include <iostream>
#include <vector>

template <typename Iter>
void print(Iter begin, Iter end) {
  while (begin != end) {
    std::cout << *begin << " ";
    begin++;
  }
  std::cout << std::endl;
}

template <typename T>
class Comp
{
public:
  bool operator()(const T& rhs1, const T& rhs2) const
  {
    return rhs1 > rhs2;
  }
};

int main() {
  std::vector<int> vec;
  vec.push_back(5);
  vec.push_back(3);
  vec.push_back(1);
  vec.push_back(6);
  vec.push_back(3);
  vec.push_back(4);
  vec.push_back(7);
  vec.push_back(3);
  vec.push_back(2);

  print(vec.begin(), vec.end());
  std::cout << "정렬 전 ----" << std::endl;


  std::vector<int>::iterator iter = std::remove(vec.begin(), vec.end(), 3);
  print(vec.begin(), vec.end());
  std::cout << "Remove 후 ----" << std::endl;
  std::cout << std::distance(vec.begin(), iter) << std::endl;
  std::cout << std::distance(vec.begin(), vec.end()) << std::endl;
  std::cout << "*iter : " << *iter << std::endl;

  print(vec.begin(), vec.end());
  std::sort(vec.begin(), vec.end(), std::greater<int>());

  std::cout << "정렬 후 ----" << std::endl;
  print(vec.begin(), vec.end());
}