#include "controller.h"

#include <iostream>
#include <thread>

Controller::Controller()
{

}

Controller::~Controller()
{

}

void Controller::call_back(File::Buffer buffer, size_t index)
{
  int num_threads = std::thread::hardware_concurrency();
  std::cout << "call_back : " << index << std::endl;
  std::cout << "num_threads : " << num_threads << std::endl;
  this->read_buffers_.push(std::make_pair(index, std::move(buffer)));
  std::pair<size_t, File::Buffer> p = std::move(this->read_buffers_.front());
  std::cout << p.second.data.get() << std::endl;
  this->read_buffers_.pop();
  // File::Buffer buffer = std::move(std::move(this->read_buffers_.front()).second);
}

void Controller::excute()
{
  auto binded_call_back = std::bind(&Controller::call_back, this, std::placeholders::_1, std::placeholders::_2);
  file_reader::read_all(binded_call_back);
}