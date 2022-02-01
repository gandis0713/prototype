#include "file1.h"

file2::file2()
{

}

file2::~file2()
{
  
}

template <typename T>
file1<T>::file1()
{

}

template <typename T>
file1<T>::~file1()
{

}

// inline void g_inline_file_func()
// {
//   std::cout << __FUNCTION__ << std::endl;
// }

void g_file_func()
{
  std::cout << __FUNCTION__ << std::endl;
}