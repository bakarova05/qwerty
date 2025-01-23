#pragma once
#include <string>
#include <vector>
#include <boost/filesystem/path.hpp>

class FileHasher {
public:
    virtual ~FileHasher() = default;
    virtual std::string hashFile(const boost::filesystem::path& filePath, size_t blockSize) = 0;
    static std::unique_ptr<FileHasher> createHasher(const std::string& algorithm);
};

