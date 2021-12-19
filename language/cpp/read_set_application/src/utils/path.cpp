#include "utils/path.h"

PathHelper::PathHelper() :
  app_path_(std::filesystem::current_path().string() + "/" + PathHelper::app_name),
  file_dir_(std::filesystem::current_path().string() + "/")
{
  // do nothing.
}

PathHelper::~PathHelper()
{
  // do nothing.
}

PathHelper& PathHelper::get_instance()
{
  static PathHelper instance;
  return instance;
}

std::string PathHelper::get_app_dir() const
{
  return this->app_path_.parent_path().string();
}

const char* PathHelper::get_app_path() const
{
  return this->app_path_.c_str();
}

const char* PathHelper::get_file_dir() const
{
  return this->file_dir_.c_str();
}