#ifndef _IEL_IO_FILE_H_
#define _IEL_IO_FILE_H_

#include <string>
#include <fstream>
#include <memory>

namespace iel {

class File {
  public:
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

  public:
    File(const char* path, const Type type);
    File(const std::string& path, const Type type);
    File(const File& file) = delete;
    File(File&& file) = delete;
    virtual ~File();

    Result open();
    void read();
    void close();
  public:
    File& operator=(const File&) = delete;
    File& operator=(File&&) = delete;

  private:
    std::string mFilePath;
    Type mType;
    std::unique_ptr<std::fstream> mStream;
};

} // namespace iel

#endif // _IEL_IO_FILE_H_