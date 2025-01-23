#pragma once
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

struct FileData {
  boost::filesystem::path filePath;
  std::vector<std::string> blockHashes;

   FileData(const boost::filesystem::path& path) : filePath(path){}
};