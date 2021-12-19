#ifndef _IEL_IO_FILE_H_
#define _IEL_IO_FILE_H_

#include <string>
#include <memory>
#include <vector>
#include <fstream>

class File {
  public:
    using size_type = size_t;
    using value_type = char;
    using data_type = std::unique_ptr<const value_type[]>;

    enum class Result {
      NoError,
      EmptyFilePath,
      CannotOpen,
      AlreadyOpen
    };

    enum class Type {
      R, // read
      W, // write
      RW // read/write
    };

    struct Buffer {
      size_type size;
      data_type data;

      Buffer();
      Buffer(size_type size, data_type data);
      ~Buffer();

      Buffer(const Buffer& text_line) = delete;
      Buffer& operator = (const Buffer& text_line) = delete;

      Buffer(Buffer&& text_line) noexcept;
      Buffer& operator = (Buffer&& text_line) noexcept;
    };

  public:
    File(const char* path, const Type type);
    File(const std::string& path, const Type type);
    File(const File& file) = delete;
    File(File&& file) = delete;
    virtual ~File();

    Result open();
    void close();

    static Buffer read_all(const char* path);
  public:
    File& operator=(const File&) = delete;
    File& operator=(File&&) = delete;

  private:
    std::string mFilePath;
    Type mType;
    std::unique_ptr<std::fstream> mStream;
};

#endif // _IEL_IO_FILE_H_