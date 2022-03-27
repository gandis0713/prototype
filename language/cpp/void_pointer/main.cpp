#include <cctype>
#include <iostream>
#include <string>

struct Test
{
  int value;
  int* pValue;
};

struct Test2
{
  short value2; 
  int* pValue2;
};



int main()
{
  Test test {};
  test.pValue = new int;
  *test.pValue = 10;
  test.value = 12;
  Test2 test2 {};
  test2.pValue2 = new int;
  *test2.pValue2 = 20;
  test2.value2 = 22;

  void* pVTest = &test;
  std::cout << "&test : " << &test << std::endl;
  std::cout << "&test.pValue : " << &test.pValue << std::endl;
  std::cout << "test.pValue : " << test.pValue << std::endl;
  std::cout << "pVTest : " << pVTest << std::endl;
  std::cout << "&pVTest : " << &pVTest << std::endl;
  std::cout << "((const void **)pVTest) : " << ((const void **)pVTest) << std::endl;
  std::cout << "((const void *)pVTest) : " << ((const void *)pVTest) << std::endl;
  std::cout << "*((const void **)pVTest) : " << *((const void **)pVTest) << std::endl;
  std::cout << "*((Test2**)pVTest) : " << *((Test2 **)pVTest) << std::endl;

  const void* pVTest2 = &test2;
  
  std::cout << "pVtest2 :: " << pVTest2 << std::endl;
  *((const void **)pVTest) = pVTest2;
  std::cout << pVTest << std::endl;
  int *pTestValue = *((int **)pVTest2);
  std::cout << "pTestValue : " << pTestValue << std::endl;

  Test *pTest = static_cast<Test*>(pVTest);
  const Test2 *pTest2 = static_cast<const Test2*>(pVTest2);

  std::cout << pTest << std::endl;
  std::cout << *pTest->pValue << std::endl;
  return 0;
}