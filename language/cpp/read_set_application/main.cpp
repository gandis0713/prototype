#include <iostream>
#include <filesystem>
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
    constexpr int size = 50000;
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

  iel::File file {PathHelper::get_instance().get_file_path(), iel::File::Type::R};
  file.read();

  
  return 0;
}