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

    AC::Scanner s{};
    s.set_program(p.str());
    std::cout << s.prog << std::endl;
    auto tokens = s.get_tokens();
    for (auto t : tokens)
        std::cout << t << std::endl;
    return EXIT_SUCCESS;
}
