#ifndef _IEL_VECTOR_H_
#define _IEL_VECTOR_H_

#include <cstddef>
#include <new>

namespace iel
{

template<typename T>
class vector
{
public:
  using size_type = size_t;
  using capacity_type = size_t;

  class iterator
  {
    public:
      iterator();
      ~iterator();

    private:
      T* _data;
      size_type _index;
  };

public:
  vector();
  ~vector();

  T* data() { return _data; };
  [[nodiscard]] constexpr size_type size() const { return _size; };
  [[nodiscard]] constexpr capacity_type capacity() const { return _capacity; };

  void reserve(const size_type size);
  void push_back(const T& data);

  iterator begin();
  iterator end();

private:
  T* _data;
  size_type _size;
  capacity_type _capacity;

};

template <typename T>
void vector<T>::reserve(const size_type size)
{
  delete[] this->data;

  this->_size = 0;
  this->_capacity = 0;

  this->_data = new (std::nothrow) T[size];
  if(this->_data != nullptr)
  {
    this->_capacity = size;
  }
}

template <typename T>
void push_back(const T& data)
{

}

}

#endif // _IEL_VECTOR_H_