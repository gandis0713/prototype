#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <string>

#include "io/file.h"
#include "utils/path.h"
#include "runner.h"

namespace fs = std::filesystem;

void prepare_test_data()
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
  prepare_test_data();

  runner::excute();
  
  return 0;
}