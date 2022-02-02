#include "bar.h"
int x = 1;

int foo() {
  bar();
  x++;
  return 1;
}