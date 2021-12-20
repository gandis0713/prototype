#ifndef _PROTOTYPE_FILE_READER_H_
#define _PROTOTYPE_FILE_READER_H_

#include <functional>
#include "utils/path.h"
#include "io/file.h"

namespace file_reader
{
  
  void read_all(std::function<void(File::Buffer, size_t)> func);

} // namespace file_reader

#endif // _PROTOTYPE_FILE_READER_H_