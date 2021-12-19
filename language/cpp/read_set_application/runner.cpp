#include "runner.h"

#include <iostream>
#include "io/file.h"
#include "utils/path.h"

namespace runner
{

  void excute()
  {
    File file {PathHelper::get_instance().get_file_path(), File::Type::R};
    std::vector<File::TextLine> text_lines = std::move(file.read_lines());

    for(const File::TextLine& text_line : text_lines)
    {
      std::cout << text_line.data.get()[0] << std::endl;
    }
  }

} // namespace runner