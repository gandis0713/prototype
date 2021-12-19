#include "file_reader.h"

#include <vector>
#include <queue>
#include <cstring>
#include <iostream>

#include "utils/path.h"
#include "io/file.h"

namespace file_reader
{
  void read_all()
  {
    constexpr int size = FILE_COUNT;
    const PathHelper& pathHelper = PathHelper::get_instance();

    std::queue<File::Buffer> read_buffers;
    // std::vector<File::Buffer> buffers;
    // buffers.reserve(size);
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
      File::Buffer buffer = File::read_byte(file_path.c_str());

      read_buffers.push(std::move(buffer));
      // buffers.push_back(std::move(buffer));

      std::cout << "file path : " << file_path << std::endl;
      
    }
    
    std::cout << "buffers.size : " << read_buffers.size() << std::endl;

    std::queue<File::Buffer> write_buffers;
    size_t data_size = 0;
    while(!read_buffers.empty())
    {
      File::Buffer buf = std::move(read_buffers.front());
      data_size += buf.size;
      read_buffers.pop();
      std::cout << "created buffer : " << buf.data.get() << std::endl;
      write_buffers.push(std::move(buf));
    }

    std::cout << "data_size : " << data_size << std::endl;

    std::unique_ptr<File::value_type[]> datas = 
      std::unique_ptr<File::value_type[]>(new (std::nothrow) File::value_type[data_size]);

    size_t count = 0;
    while (!write_buffers.empty())
    {
      File::Buffer buf = std::move(write_buffers.front());
      write_buffers.pop();
      memcpy(datas.get() + (count * buf.size), buf.data.get(), buf.size);
      count++;
    }

    std::string file_temp_dir;
    file_temp_dir.append(pathHelper.get_file_dir());
    file_temp_dir.append("temp/");

    std::string file_path;
    file_path.append(file_temp_dir);
    file_path.append(PathHelper::file_name);
    file_path.append(".");
    file_path.append(PathHelper::file_extension);
    
    std::fstream file {file_path, std::ios::out};
    if(file.is_open()) 
    {
      file << datas.get();
    }
    file.close();

    // std::filesystem::remove_all(file_temp_dir);
    
  }

} // namespace file_reader