#include "FileHasher.h"
#include "BlockHasher.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
 #include <boost/filesystem/path.hpp>


class FileHasherImpl : public FileHasher {
public:
    FileHasherImpl(std::unique_ptr<BlockHasher> blockHasher) : blockHasher_(std::move(blockHasher)) {};

     std::string hashFile(const boost::filesystem::path& filePath, size_t blockSize) override{
        std::ifstream file(filePath.string(), std::ios::binary);
        if (!file.is_open()) {
            return "";
        }

        std::string fileHash = "";
        std::vector<char> buffer(blockSize);
        while(file.good()){
           file.read(buffer.data(), buffer.size());
           if(file.gcount() > 0){
              std::vector<char> block(buffer.begin(), buffer.begin() + file.gcount());
                fileHash+= blockHasher_->hashBlock(block) + "|";
             }
         }
      return fileHash;
    }

private:
   std::unique_ptr<BlockHasher> blockHasher_;
};



std::unique_ptr<FileHasher> FileHasher::createHasher(const std::string& algorithm) {
   std::unique_ptr<BlockHasher> blockHasher = BlockHasher::createHasher(algorithm);
    if (blockHasher) {
      return std::make_unique<FileHasherImpl>(std::move(blockHasher));
    }
  return nullptr;
}



std::unique_ptr<FileHasher> FileHasher::createHasher(const std::string& algorithm) {
    if (algorithm == "crc32") {
        return std::make_unique<CRC32Hasher>();
    }
    else if (algorithm == "md5") {
        return std::make_unique<MD5Hasher>();
    }
    return nullptr;
}