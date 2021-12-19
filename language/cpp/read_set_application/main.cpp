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

  int count = 0;
  constexpr int size = FILE_COUNT;
  while(count < size)
  {

    std::string file_temp_dir;
    file_temp_dir.append(pathHelper.get_file_dir());
    file_temp_dir.append("temp/");
    if(!std::filesystem::exists(file_temp_dir))
    {
      std::filesystem::create_directory(file_temp_dir);
    }

    std::string file_path;
    file_path.append(file_temp_dir);
    file_path.append(PathHelper::file_name);
    file_path.append(std::to_string(count));
    file_path.append(".");
    file_path.append(PathHelper::file_extension);
    
    std::fstream file {file_path, std::ios::out};
    if(file.is_open()) 
    {
      file << pathHelper.get_file_dir() << std::to_string(count) << "\n";
      // file << std::to_string(count) << "\n";
    }
    file.close();
    count++;      
  }
}

int main(int argc, char *argv[])
{
  prepare_test_data();

  runner::excute();
  
  return 0;
}