#include <iostream>
using namespace std;
int main() {
  int t;
  while (true) {
    std::cin >> t;
    std::cout << "입력 :: " << t << std::endl;
    if (t == 0) break;
  }
}