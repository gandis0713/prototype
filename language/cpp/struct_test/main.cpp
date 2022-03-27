#include <iostream>


struct Test
{
  int value = 10;
};



int main()
{
    const int value = 0;
    const int* const test = &value;


    return 0;
}
