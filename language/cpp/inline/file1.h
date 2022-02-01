#include <iostream>

class file2
{
public:
  file2();
  ~file2();
  void print();
};

void file2::print()
{
  std::cout << __FUNCTION__ << std::endl;
}

template <typename T>
class file1
{
public:
  file1();
  ~file1();

  void print_T(T* t = nullptr);
  void print();
};

template <typename T>
void file1<T>::print_T(T* t)
{
  std::cout << __FUNCTION__ << std::endl;
}

template <typename T>
void file1<T>::print()
{
  std::cout << __FUNCTION__ << std::endl;
}

// inline void g_inline_file_func();
// inline void g_inline_file_func()
// {
//   std::cout << __FUNCTION__ << std::endl;
// }


void g_file_func();