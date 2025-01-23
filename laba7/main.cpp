#include "CLIParser.h"
#include "DuplicateFinder.h"
#include <iostream>
#include <boost/filesystem.hpp>

int main(int argc, char** argv) {
    CLIParser parser(argc, argv);
    if (!parser.isValid()) {
        std::cerr << "Error parsing command line arguments: " << parser.getErrorMessage() << std::endl;
        return 1;
    }

    Config config = parser.getConfig();

   if(config.includeDirs.empty()){
      std::cerr << "No include directories specified" << std::endl;
          return 1;
   }

   for(auto& exclude : config.excludeDirs){
      if(std::find(config.includeDirs.begin(), config.includeDirs.end(), exclude) != config.includeDirs.end()){
         std::cerr << "Include directory and exclude directory are the same: " << exclude << std::endl;
           return 1;
       }
   }


    DuplicateFinder finder(config);
    finder.findDuplicates();
    finder.printDuplicates();
    return 0;
}