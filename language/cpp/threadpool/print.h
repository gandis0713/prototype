#ifndef _PRINT_H_
#define _PRINT_H_

#include <iostream>
// #include <sstream>
// #include <fstream>
// #include <mutex>


// class Print
// {
// 	std::ostringstream g_buf;
// 	std::ofstream g_fout;
// 	std::mutex g_mu_print;
// };

// void _print()
// {
//     g_fout << g_buf.str() << std::endl;
//     g_buf.clear();
// }

// template<typename Arg, typename... Args>
// void _print(Arg&& arg, Args&&... args)
// {
//     g_buf << std::forward<Arg>(arg) << ", ";
//     _print(std::forward<Args>(args)...);
// }

// template<typename... Args>
// void print(Args&&... args)
// {
//     std::unique_lock<std::mutex> lock(g_mu_print);
//     _print(std::forward<Args>(args)...);
// }




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

#endif // _PRINT_H_