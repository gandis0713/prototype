#ifndef _IEL_IO_FILE_H_
#define _IEL_IO_FILE_H_

#include <string>
#include <memory>
#include <vector>
#include <fstream>

class File {

  using size_type = size_t;
  using text_type = std::unique_ptr<char[]>;
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

    struct TextLine {
      size_type size;
      text_type data;

      TextLine(size_type size, text_type data);
      ~TextLine();

      TextLine(const TextLine& text_line) = delete;
      TextLine& operator = (const TextLine& text_line) = delete;

      TextLine(TextLine&& text_line) noexcept;
      TextLine& operator = (TextLine&& text_line) noexcept;
    };

  public:
    File(const char* path, const Type type);
    File(const std::string& path, const Type type);
    File(const File& file) = delete;
    File(File&& file) = delete;
    virtual ~File();

    Result open();
    std::vector<TextLine> read_lines();
    void close();
  public:
    File& operator=(const File&) = delete;
    File& operator=(File&&) = delete;

  private:
    std::string mFilePath;
    Type mType;
    std::unique_ptr<std::fstream> mStream;
};

#endif // _IEL_IO_FILE_H_