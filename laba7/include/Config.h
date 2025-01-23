#pragma once
#include <string>
#include <vector>

struct Config {
    std::vector<std::string> includeDirs;
    std::vector<std::string> excludeDirs;
    int scanLevel = -1; // -1 - infinite
    size_t minFileSize = 1;
    std::vector<std::string> fileMasks;
    size_t blockSize = 4096;
    std::string hashAlgorithm = "crc32"; //default algorithm
};