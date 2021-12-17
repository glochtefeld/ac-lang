cmake_minimum_required(VERSION 3.16)
project(AddingCalc VERSION 0.1.0 LANGUAGES C CXX)



add_library(scanner
    src/scanner/scanner.cpp
    include/scanner/scanner.hpp
    include/scanner/token.hpp
    include/magic_enum/magic_enum.hpp
)
target_compile_features(scanner PUBLIC cxx_std_17)
target_include_directories(scanner PUBLIC include)


add_executable(ac src/main.cpp)
target_link_libraries(ac PRIVATE scanner)
