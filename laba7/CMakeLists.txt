cmake_minimum_required(VERSION 3.10)
project(DuplicateFinder)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS filesystem program_options system)
find_package(OpenSSL REQUIRED)
include_directories(${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})

add_executable(duplicate_finder main.cpp src/CLIParser.cpp src/DuplicateFinder.cpp src/FileHasher.cpp)
target_link_libraries(duplicate_finder Boost::filesystem Boost::program_options Boost::system OpenSSL::Crypto)