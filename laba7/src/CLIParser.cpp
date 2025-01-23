#include "CLIParser.h"
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <iterator>

CLIParser::CLIParser(int argc, char** argv) {
    try {
        namespace po = boost::program_options;
        po::options_description desc("Allowed options");
        desc.add_options()
            ("include-dir,i", po::value<std::vector<std::string>>(), "Directories to scan")
            ("exclude-dir,e", po::value<std::vector<std::string>>(), "Directories to exclude")
            ("scan-level,l", po::value<int>(), "Scan level")
            ("min-size,m", po::value<size_t>(), "Minimum file size")
            ("file-mask,f", po::value<std::vector<std::string>>(), "File masks")
            ("block-size,s", po::value<size_t>(), "Block size")
            ("hash-algorithm,a", po::value<std::string>(), "Hash algorithm (crc32, md5)")
        ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("include-dir")) {
            config_.includeDirs = vm["include-dir"].as<std::vector<std::string>>();
        }
        if (vm.count("exclude-dir")) {
            config_.excludeDirs = vm["exclude-dir"].as<std::vector<std::string>>();
        }
        if (vm.count("scan-level")) {
           config_.scanLevel = vm["scan-level"].as<int>();
        }
        if (vm.count("min-size")) {
           config_.minFileSize = vm["min-size"].as<size_t>();
        }
         if (vm.count("file-mask")) {
           config_.fileMasks = vm["file-mask"].as<std::vector<std::string>>();
           for(auto& mask : config_.fileMasks){
             boost::algorithm::to_lower(mask);
           }
        }
       if (vm.count("block-size")) {
            config_.blockSize = vm["block-size"].as<size_t>();
       }
       if (vm.count("hash-algorithm")) {
           config_.hashAlgorithm = vm["hash-algorithm"].as<std::string>();
       }

    } catch (const boost::program_options::error& e) {
        valid_ = false;
        errorMessage_ = e.what();
        return;
    }
}

Config CLIParser::getConfig() {
    return config_;
}

bool CLIParser::isValid() const {
    return valid_;
}

std::string CLIParser::getErrorMessage() const {
    return errorMessage_;
}