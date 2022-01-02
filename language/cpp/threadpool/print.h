#include <iostream>

template <typename Arg>
void print(Arg arg)
{
	std::cout << arg << std::endl;
}

template <typename Arg, typename... Args>
void print(Arg arg, Args... args)
{
	std::cout << arg << ", ";
	print(args...);
}