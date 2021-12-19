#include <iostream>
#include <memory>
#include <exception>
#include <vector>

using namespace std;

using unique_void_ptr = std::unique_ptr<void, void(*)(void const*)>;

template<typename T>
unique_void_ptr unique_void(T * ptr)
{
  return unique_void_ptr(ptr, [](void const * data) {
    T const * p = static_cast<T const*>(data);
    delete [] p;
  });
}

class A 
{
public:
  A(){
    cout << "A()" << endl;
  }

  A(const A& a) {
    cout << "A&" << endl;
  }

  A(A&& a) {
    cout << "A&&" << endl;
  }

  A& operator = (const A& a) {
    cout << "A& =" << endl;
    return *this;
  }

  A& operator = (A&& a) {
    cout << "A&& =" << &a << endl;
    return *this;
  }

  virtual ~A() {
    cout << "~A()" << endl;
  }
};

int main()
{
  {
    // unique_void_ptr a = unique_void(new A[5]);
    std::unique_ptr<A[]> p = std::make_unique<A[]>(5);
    std::unique_ptr<A[]> p2 = std::move(p);
  }
  return 0;
}