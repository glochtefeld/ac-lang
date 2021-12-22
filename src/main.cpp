#include "scanner/scanner.hpp"
#include "parser/parser.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>


int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: ac (COMMAND | FILE)\n"
            << "COMMAND:\n" << "\t-c PROGRAM\n\t\tCommand mode: run a one line program read from stdin.\n"
            << "FILE:\n" << "\t Interpret the file at the provided path as a program." 
            << std::endl;
        return EXIT_SUCCESS;
    }
    std::stringstream program;

    if (std::string(argv[1]) != "-c") {
        std::ifstream file(argv[1],std::ifstream::in);
        if (!file.is_open()) {
            std::cout << "ERROR: file " << argv[1] << " not found" << std::endl;
            return EXIT_FAILURE;
        }
        std::stringstream program;
        program << file.rdbuf();
        file.close();
    }
    else 
        program << argv[2];

    std::cout << program.str() << std::endl;

    AC::Scanner s;
    AC::Parser p;
    s.set_program(program.str());
    try {
        auto tokens = s.get_tokens();
        std::cout << "Printing tokens..." << std::endl;
        for (auto t : tokens)
            std::cout << t << std::endl;
        std::cout << "Loading tokens..." << std::endl;
        p.set_tokens(tokens);
        std::cout << "Checking Program... ";
        if (p.check_program())
            std::cout << "Program compiles." << std::endl;
        else
            std::cout << "Program failed compilation." << std::endl;
    }
    catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
