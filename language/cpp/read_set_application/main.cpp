#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <string>

#include "io/file.h"
#include "utils/path.h"

namespace fs = std::filesystem;

void prepare_test()
{
  PathHelper& pathHelper = PathHelper::get_instance();
  std::fstream file {pathHelper.get_file_path(), std::ios::out};
  if(file.is_open()) 
  {
    unsigned int count = 0;
    constexpr int size = 2;
    while(count < size)
    {
      file << pathHelper.get_file_dir() << std::to_string(count) << "\n";
      count++;      
    }
    file.close();
  }
}

int main(int argc, char *argv[])
{
  prepare_test();

  File file {PathHelper::get_instance().get_file_path(), File::Type::R};
  std::vector<File::TextLine> text_lines = std::move(file.read_lines());

  std::cout << text_lines.size() << std::endl;
  for(const File::TextLine& text_line : text_lines)
  {
    std::cout << text_line.data.get() << std::endl;
  }
  
  return 0;
}