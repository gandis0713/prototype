// #include <iostream>
// using namespace std;
#include "global.h"

int shared_1_global_num = 0;

int get_shared_1_global_num()
{
    // cout << "get_shared_1_global_num() : " << shared_1_global_num << endl;
    return shared_1_global_num;
}

int& get_shared_1_global_num_reference()
{
    // cout << "get_shared_1_global_num_reference() : " << &shared_1_global_num << endl;
    return shared_1_global_num;
}

void print_shared_1_global_num()
{
    // cout << "print_shared_1_global_num() : " << shared_1_global_num << endl;
}
