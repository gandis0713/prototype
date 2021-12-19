#include "io/file.h"
#include <iostream>
#include <cstring>

File::TextLine::TextLine(size_type size, text_type data) : 
  size(size), 
  data(std::move(data))
{
  std::cout << "TextLine()" << std::endl;
}

File::TextLine::~TextLine()
{
  std::cout << "~TextLine()" << std::endl;
}

File::TextLine::TextLine(TextLine&& text_line) noexcept : 
  size(text_line.size), 
  data(std::move(text_line.data))
{
  std::cout << "TextLine(TextLine&&)" << std::endl;
}

File::TextLine& File::TextLine::operator = (TextLine&& text_line) noexcept
{
  std::cout << "operator(TextLine&=&&)" << std::endl;
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

std::vector<File::TextLine> File::read_lines()
{
  std::vector<TextLine> text_lines;
  if (mStream->is_open()) {
      std::string s;
      while (std::getline(*mStream, s)) {
          std::cout << "s : " << s << std::endl;

          // std::unique_ptr<File::value_type[]> text_data = std::make_unique<File::value_type[]>(s.size());
          std::unique_ptr<File::value_type[]> text_data = 
            std::unique_ptr<File::value_type[]>(new (std::nothrow) File::value_type[s.size()]);

          memcpy(text_data.get(), s.c_str(), sizeof(File::value_type) * s.size());

          if(text_data != nullptr) 
          {
            // TextLine text_line {s.size(), s};
            // text_lines.push_back(std::move(text_line));
            text_lines.emplace_back(s.size(), std::move(text_data));
          }

      }
      mStream->close();
  }

  return text_lines;
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