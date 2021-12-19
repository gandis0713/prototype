#include "io/file.h"
#include <iostream>

namespace iel {

File::File(const char* path, const Type type): 
  mFilePath(path), 
  mType(type) {

  this->open();
}

File::File(const std::string& path, const Type type): 
  mFilePath(path), 
  mType(type) {

  this->open();
}

File::~File() {
  this->close();
}

void File::read()
{
  if (mStream->is_open()) {
      std::string s;
      while (*mStream) {
          std::getline(*mStream, s);  
          std::cout << s << std::endl;
      }
      mStream->close();
  }
}

File::Result File::open() {
  if(mFilePath.empty()) 
    return Result::EmptyFilePath;

  if(mStream != nullptr) {
    if(mStream->is_open()) 
      return Result::AlreadyOpen;

    mStream.reset();
  }

  switch(mType) {
    case Type::R:
    mStream = std::make_unique<std::fstream>(mFilePath, std::ios::in);
    break;
    case Type::W:
    mStream = std::make_unique<std::fstream>(mFilePath, std::ios::in);
    break;
    case Type::RW:
    default:
    mStream = std::make_unique<std::fstream>(mFilePath, std::ios::in | std::ios::out);
    break;
  }

  return File::Result::NoError;
}

void File::close() {
  if(mStream != nullptr) {
    mStream->close();
  }
}


} // namespace iel