#include "runner.h"

#include <iostream>
#include "file_reader.h"
#include "utils/path.h"

namespace runner
{

  void excute()
  {
    file_reader::read_all();
    // File file {PathHelper::get_instance().get_file_path(), File::Type::R};
    // std::vector<File::TextLine> text_lines = std::move(file.read_lines());

    // for(const File::TextLine& text_line : text_lines)
    // {
    //   std::cout << text_line.data.get() << std::endl;
    // }
  }

} // namespace runner