#include "io/file.h"
#include <iostream>
#include <cstring>
#include <thread>

File::Buffer::Buffer() : 
  size(0), 
  data(nullptr)
{
  // std::cout << "Buffer()" << std::endl;
}

File::Buffer::Buffer(size_type size, data_type data) : 
  size(size), 
  data(std::move(data))
{
  // std::cout << "Buffer(size_type size, data_type data)" << std::endl;
}

File::Buffer::~Buffer()
{
  // std::cout << "~Buffer()" << std::endl;
}

File::Buffer::Buffer(Buffer&& text_line) noexcept :
  size(text_line.size), 
  data(std::move(text_line.data))
{
  // std::cout << "Buffer(Buffer&&)" << std::endl;
}

File::Buffer& File::Buffer::operator = (Buffer&& text_line) noexcept
{
  // std::cout << "operator(Buffer&=&&)" << std::endl;
  if(this != &text_line)
  {
    this->size = text_line.size;
    
    if(this->data != nullptr) this->data.reset();
    this->data = std::move(text_line.data);
  }
  return *this;
}

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

File::Buffer File::read_byte(const char* path)
{
  File::Buffer buffer;
  // if (std::ifstream is{path, std::ios::binary | std::ios::ate}) {
  //   auto size = is.tellg();
  //   std::string str(size, '\0');  // construct string to stream size
  //   is.seekg(0);
  //   if (is.read(&str[0], size)) 
  //   {
  //     buffer.size = str.size();
  //     std::unique_ptr<value_type[]> data = 
  //       std::unique_ptr<value_type[]>(new (std::nothrow) value_type[buffer.size]);
  //     if(data != nullptr)
  //     {
  //       buffer.data = std::move(data);
  //     }
  //   }
  // }
  if(std::ifstream file{path, std::ios::in})
  {
    std::string s;
    std::string text;
    while(std::getline(file, s))
    {
      text += s;
    }
    const size_t size = text.size();
    buffer.size = size + 1;
    std::unique_ptr<value_type[]> data = 
      std::unique_ptr<value_type[]>(new (std::nothrow) value_type[buffer.size]);
    if(data != nullptr)
    {
      memcpy(data.get(), text.c_str(), sizeof(File::value_type) * size);
      data[0] = '\n';
      buffer.data = std::move(data);
    }
  }


  // std::cout << "buffer.size : " << buffer.size << std::endl;
  // std::cout << "buffer.data : " << buffer.data.get() << std::endl;

  return buffer;
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