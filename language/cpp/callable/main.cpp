// #include <functional>
// #include <iostream>
// #include <string>

// int func(const std::string& a) {
//   std::cout << "func is called. " << a << std::endl;
//   return 0;
// }

// struct SData {
//   void operator()(char c) { std::cout << "SData operator() is called : " << c << std::endl; }
//   void operator()(int n) { std::cout << "SData operator() is called : " << n << std::endl; }
// };

// int main() {
//   std::function<int(const std::string&)> f1 = func;
//   std::function<void(char)> f2_0 = SData();
//   std::function<void(int)> f2_1 = SData();
//   std::function<void(void)> f3 = []() { std::cout << "Lamda function is called." << std::endl; };

//   f1("hello");
//   f2_0('c');
//   f2_1(10000);
//   f3();
// }

// #include <functional>
// #include <iostream>

// struct S {
//   int data;
//   S(int data) : data(data) { std::cout << "일반 생성자 호출!" << std::endl; }
//   S(const S& s) {
//     std::cout << "복사 생성자 호출!" << std::endl;
//     data = s.data;
//   }

//   S(S&& s) {
//     std::cout << "이동 생성자 호출!" << std::endl;
//     data = s.data;
//   }
// };

// void do_something(S& s1, const S& s2) { s1.data = s2.data + 3; }

// int main() {
//   S s1(1), s2(2);

//   std::cout << "Before : " << s1.data << std::endl;

//   std::reference_wrapper<S> sr = s1; 
//   auto do_something_with_s1 =
//       std::bind(do_something, sr, std::placeholders::_1);
//   do_something_with_s1(s2);

//   std::cout << "After :: " << s1.data << std::endl;
// }

int main()
{
  int a = 1;
  int b = a + 1;
  return 0;
}