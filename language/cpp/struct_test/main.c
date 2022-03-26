// // #include <iostream>

#include "stdio.h"

struct Test
{
  int value;
};

typedef struct Test Test;

// typedef struct Test _Test;

// typedef struct Test {} Test;
void print(const Test* test)
{
  // std::cout << test->value << std::endl;
  // printf("size : %lu \n", sizeof(test));
  // printf("size : %lu \n", sizeof(*test));
  printf("size : %lu \n", sizeof(Test));
  // printf("size : %lu \n", sizeof(_Test));
  printf("value : %d \n", test->value);
}



int main()
{
   Test test;
   test.value = 10;
  // _Test _test;
  print(&test);
  // print(&_test);



  return 0;
}

// #include <stdio.h>
// static char T = 'a';
// int main(int argc, char** argv) {
//     struct T { char X[2]; };
//     printf("size of T is %zu\n", sizeof(T));
// }

// #include <stdio.h>
// static char T = 'a';
// int main(int argc, char** argv) {
//     struct T { char X[2]; };
//     printf("size of T is %zu\n", sizeof T);
// }

// #include <stdio.h>
// int main(int argc, char** argv) {
//     static char T = 'a';
//     struct T { char X[2]; };
//     printf("size of T is %zu\n", sizeof T);
// }

// #include <stdio.h>
// static char T = 'a';
// int main(int argc, char** argv) {
//   struct T { char X[2]; };
//   printf("size of T is %zu\n", sizeof(T));
//   static char T = 'a';
//   printf("size of T is %zu\n", sizeof(T));
// }