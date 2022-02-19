#include <iostream>
#include <string>

class CString
{
public:

  CString()
  {
    std::cout << "CString()" << std::endl;
  }

  CString(const char* c)
  {
    std::cout << "CString() : " << c << std::endl;
    str = c;
  }

  CString(const CString& rhs)
  {
    std::cout << "CString(const CString& rhs) : " << rhs.str << std::endl;
    this->str = rhs.str;
  }

  CString(CString&& rhs) noexcept
  {
    std::cout << "CString(CString&& rhs) : " << rhs.str << std::endl;
    this->str = rhs.str;
  }

  ~CString() 
  {
    std::cout << "~CString" << std::endl;
  }

  CString operator+(const CString& rhs)
  {
    std::string str;
    str = this->str + rhs.str;

    CString cstr;
    cstr.setString(str);

    return cstr;
  }

  void setString(const std::string& str)
  {
    this->str = str;
  }

private:
  std::string str;
};

int main()
{
  CString str1 = "abc";
  CString str2 = "def";

  CString str3 = str1 + str2;
  CString str4(static_cast<CString&&>(str3));
  CString str5(str4);

  int value = 10;
  int&& r_value_ref = static_cast<int&&>(value); 

  return 0;
}