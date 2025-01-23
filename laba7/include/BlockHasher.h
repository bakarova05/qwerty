#pragma once
#include <string>
#include <vector>
#include <memory>

class BlockHasher {
public:
    virtual ~BlockHasher() = default;
    virtual std::string hashBlock(const std::vector<char>& block) = 0;
    static std::unique_ptr<BlockHasher> createHasher(const std::string& algorithm);
};

