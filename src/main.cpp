#include "scanner/scanner.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>


int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: ac FILE" <<std::endl;
        return EXIT_SUCCESS;
    }
    std::ifstream file(argv[1],std::ifstream::in);
    if (!file.is_open()) {
        std::cout << "ERROR: file " << argv[1] << " not found";
        return EXIT_FAILURE;
    }
    std::stringstream p;
    p << file.rdbuf();
    file.close();
    std::cout << p.str() << std::endl;

    AC::Scanner s{};
    s.set_program(p.str());
    try {
    auto tokens = s.get_tokens();
    for (auto t : tokens)
        std::cout << t << std::endl;
    }
    catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
