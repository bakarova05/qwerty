#pragma once
#include <string>
#include "Config.h"

class CLIParser {
public:
    CLIParser(int argc, char** argv);
    Config getConfig();
    bool isValid() const;
    std::string getErrorMessage() const;

private:
    Config config_;
    bool valid_ = true;
    std::string errorMessage_;
};