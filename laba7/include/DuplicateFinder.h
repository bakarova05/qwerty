#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <boost/filesystem.hpp>
#include "Config.h"
#include "FileData.h"

class DuplicateFinder {
public:
    DuplicateFinder(const Config& config);
    void findDuplicates();
    void printDuplicates();

private:
    void scanDirectories(const boost::filesystem::path& dir, int level);
    std::vector<std::string> getFileBlockHashes(const boost::filesystem::path& filePath);
    bool isFileAllowed(const boost::filesystem::path& filePath) const;
    Config config_;
    std::vector<FileData> fileDataList_;

};