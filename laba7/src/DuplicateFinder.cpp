#include "DuplicateFinder.h"
#include "FileHasher.h"
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <sstream>


DuplicateFinder::DuplicateFinder(const Config& config) : config_(config) {}

void DuplicateFinder::scanDirectories(const boost::filesystem::path& dir, int level) {
    if (level == 0) return;
     if (boost::filesystem::is_directory(dir)) {
         for (const auto& entry : boost::filesystem::directory_iterator(dir)) {
            if (boost::filesystem::is_regular_file(entry)) {
               boost::filesystem::path filePath = entry.path();
                if(isFileAllowed(filePath)){
                   std::vector<std::string> blockHashes = getFileBlockHashes(filePath);
                   if (!blockHashes.empty()) {
                       FileData fileData(filePath);
                        fileData.blockHashes = blockHashes;
                        fileDataList_.push_back(fileData);
                   }
              }
          } else if (boost::filesystem::is_directory(entry) && level != 0) {
             scanDirectories(entry.path(), level - 1);
             }
         }
    }
}


std::vector<std::string> DuplicateFinder::getFileBlockHashes(const boost::filesystem::path& filePath){
     if (boost::filesystem::file_size(filePath) < config_.minFileSize) {
          return {};
      }
      auto hasher = FileHasher::createHasher(config_.hashAlgorithm);
        if (!hasher) {
           std::cerr << "Invalid hashing algorithm: " << config_.hashAlgorithm << std::endl;
            return {};
       }
       std::string fileHash = hasher->hashFile(filePath, config_.blockSize);
         if(fileHash.empty()){
           return {};
        }

     std::vector<std::string> blockHashes;
     std::stringstream ss(fileHash);
     std::string blockHash;
    while(getline(ss, blockHash, '|')){
       blockHashes.push_back(blockHash);
     }
    return blockHashes;
}

bool DuplicateFinder::isFileAllowed(const boost::filesystem::path& filePath) const {
       if(config_.fileMasks.empty()){
           return true;
       }

    std::string filename = filePath.filename().string();
   boost::algorithm::to_lower(filename);

    for (const auto& mask : config_.fileMasks) {
        if(filename.length() >= mask.length()){
           std::string mask_from_filename = filename.substr(filename.length() - mask.length(), mask.length());
            if(mask_from_filename == mask){
               return true;
             }
         }
          else if(filename == mask){
             return true;
         }
     }

    return false;
}



void DuplicateFinder::findDuplicates() {
  for (const auto& dir : config_.includeDirs) {
       boost::filesystem::path path(dir);
       if(boost::filesystem::exists(path) && boost::filesystem::is_directory(path)) {
           scanDirectories(path, config_.scanLevel);
         }else{
              std::cerr << "Invalid directory path: " << dir << std::endl;
         }
    }

}


void DuplicateFinder::printDuplicates() {
  std::unordered_map<std::string, std::vector<boost::filesystem::path>> hashToFilePathsMap;
  for (const auto& fileData : fileDataList_){
        std::string combinedHash = "";
        for(const auto& hash : fileData.blockHashes){
             combinedHash += hash + "|";
        }
        hashToFilePathsMap[combinedHash].push_back(fileData.filePath);
    }

    for (const auto& pair : hashToFilePathsMap) {
        if (pair.second.size() > 1) {
           for (const auto& path : pair.second) {
                std::cout << path.string() << std::endl;
            }
            std::cout << std::endl; // Separator for duplicate groups
        }
    }
}