cmake_minimum_required(VERSION 3.16)
project(AddingCalc VERSION 0.1.0 LANGUAGES C CXX)



add_library(scanner
    src/scanner/scanner.cpp
    include/scanner/scanner.hpp
    include/scanner/token.hpp
)
target_compile_features(scanner PUBLIC cxx_std_17)
target_include_directories(scanner PUBLIC include)


add_executable(ac src/main.cpp)
target_link_libraries(ac PRIVATE scanner)

add_library(Catch2 INTERFACE)
target_include_directories(Catch2 INTERFACE external)

add_executable(ac-tests 
    src/scanner/scanner.test.cpp
    src/main.test.cpp
)
target_link_libraries(ac-tests PRIVATE Catch2)
target_link_libraries(ac-tests PRIVATE scanner)

