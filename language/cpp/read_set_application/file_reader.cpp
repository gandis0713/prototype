#include "file_reader.h"

#include <vector>
#include <iostream>

#include "utils/path.h"
#include "io/file.h"

namespace file_reader
{
  void read_all()
  {
    constexpr int size = FILE_COUNT;
    const PathHelper& pathHelper = PathHelper::get_instance();

    for(int i = 0; i < size; i++) 
    {

      std::string file_temp_dir;
      file_temp_dir.append(pathHelper.get_file_dir());
      file_temp_dir.append("temp/");

      std::string file_path;
      file_path.append(file_temp_dir);
      file_path.append(PathHelper::file_name);
      file_path.append(std::to_string(i));
      file_path.append(".");
      file_path.append(PathHelper::file_extension);
      File::Buffer buffer = std::move(File::read_all(file_path.c_str()));

      // std::cout << "file path : " << file_path << std::endl;
    }

  }

} // namespace file_reader