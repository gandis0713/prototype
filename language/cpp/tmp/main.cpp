#include <iostream>
// #include <type_traits>

template <typename T>
class is_void
{
public:
    static constexpr bool value = false;
};

template <>
class is_void<void>
{
    static constexpr bool value = true;
};

template <typename T>
void print_type()
{
    if(std::is_void<T>::value)
    {
        std::cout << "void" << std::endl;
    }
    else
    {
        std::cout << "not void" << std::endl;
    }
}

template <typename T, >
void only_integer(const T& t) {
  static_assert(std::is_integral<T>::value);
  std::cout << "T is an integer \n";
}

int main() 
{

    std::cout << "test" << std::endl;
    print_type<void>();
    print_type<int>();
    print_type<void*>();

      int n = 3;
  only_integer(3.f);
    return 0;
}
