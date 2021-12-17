#ifndef AC_SCANNER
#define AC_SCANNER
#include <vector>
#include <string>
#include <exception>
#include "token.hpp"
namespace AC {
class Scanner {
private:
    unsigned int cur_pos{};
    std::vector<Token> tokens{};
    const std::string nums = "0123456789";
    const std::string letters = "abcdeghjklmnoqrstuvwxyz";
public:
    std::string prog;


private:
    bool is_num(char n);
    bool is_var(char n);
    char peek();
    void advance();
    Token scan();
    Token scan_digit();

public:
    std::vector<Token> get_tokens();
    void set_program(const std::string& s);

};
}
#endif
