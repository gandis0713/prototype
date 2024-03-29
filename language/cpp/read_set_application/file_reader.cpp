#include "file_reader.h"

#include <vector>
#include <queue>
#include <cstring>
#include <iostream>
#include <thread>
#include <future>


namespace file_reader
{
  void read_all(std::function<void(File::Buffer, size_t)> func)
  {
    constexpr int size = FILE_COUNT;
    const PathHelper& pathHelper = PathHelper::get_instance();

    // std::vector<File::Buffer> buffers;
    // buffers.reserve(size);
    for(int i = 0; i < size; i++) 
    {

      std::future<void> result = std::async(std::launch::async, [call_back = func, index = i]
      {
        std::string file_temp_dir;
        const PathHelper& pathHelper = PathHelper::get_instance();
        file_temp_dir.append(pathHelper.get_file_dir());
        file_temp_dir.append("temp/");

        std::string file_path;
        file_path.append(file_temp_dir);
        file_path.append(PathHelper::file_name);
        file_path.append(std::to_string(index));
        file_path.append(".");
        file_path.append(PathHelper::file_extension);
        File::Buffer buffer = File::read_byte(file_path.c_str());

        call_back(std::move(buffer), index);
      });
      
    }



    
    std::cout << "buffers.size : " << read_buffers.size() << std::endl;
    std::cout << "read_buffers.size() : " << read_buffers.size() << std::endl;

    std::queue<File::Buffer> write_buffers;
    size_t data_size = 0;
    while(!read_buffers.empty())
    {
      File::Buffer buf = std::move(read_buffers.front());
      data_size += buf.size;
      read_buffers.pop();
      // std::cout << "created buffer : " << buf.data.get() << std::endl;
      write_buffers.push(std::move(buf));
    }

    std::cout << "data_size : " << data_size << std::endl;
    std::cout << "write_buffers.size() : " << write_buffers.size() << std::endl;

    std::unique_ptr<File::value_type[]> datas = 
      std::unique_ptr<File::value_type[]>(new (std::nothrow) File::value_type[data_size]);

    if(datas == nullptr)
    {
      std::cout << "datas null." << std::endl;
      return;
    }

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
    
    std::cout << "file_path :  " << file_path << std::endl;
    std::cout << "datas.get() :  " << datas.get() << std::endl;
    std::fstream file {file_path, std::ios::out};
    if(file.is_open()) 
    {
      file << datas.get();
    }
    file.close();

    // std::filesystem::remove_all(file_temp_dir);
    
  }

} // namespace file_reader