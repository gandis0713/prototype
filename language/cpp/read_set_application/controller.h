#ifndef _PROTOTYPE_CONTROLLER_H_
#define _PROTOTYPE_CONTROLLER_H_

#include <queue>

#include "file_reader.h"
#include "file_writer.h"
#include "utils/path.h"

class Controller
{
public:
  Controller();
  ~Controller();

  void excute();
  void call_back(File::Buffer buffer, size_t index);

private:
    std::queue<std::pair<size_t, File::Buffer>> read_buffers_;
};


#endif // _PROTOTYPE_CONTROLLER_H_