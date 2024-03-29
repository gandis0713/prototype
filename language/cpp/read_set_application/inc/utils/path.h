#ifndef _PROTOTYPE_UTILS_PATH_H_
#define _PROTOTYPE_UTILS_PATH_H_

#include <string>
#include <filesystem>

class PathHelper{
public:
  static constexpr char app_name[] = "main.out";
  static constexpr char file_name[] = "main_file";
  static constexpr char file_extension[] = "txt";

public:
  PathHelper();
  ~PathHelper();
  PathHelper(const PathHelper&) = delete;
  PathHelper(PathHelper&&) = delete;
  PathHelper& operator = (const PathHelper&) = delete;
  PathHelper& operator = (PathHelper&&) = delete;

  static PathHelper& get_instance();

  std::string get_app_dir() const;
  const char* get_app_path() const;
  const char* get_file_dir() const;

private:
  std::filesystem::path app_path_;
  std::filesystem::path file_dir_;
};

#endif // _PROTOTYPE_UTILS_PATH_H_