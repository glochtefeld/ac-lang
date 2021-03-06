#ifndef AC_SCANNER
#define AC_SCANNER
#include "token.hpp"
#include <vector>
#include <string>
#include <stdexcept>
namespace AC {
class Scanner {
private:
    unsigned int cur_pos{};
    std::vector<Token> tokens{};
    const std::string nums = "0123456789";
    const std::string letters = "abcdeghjklmnoqrstuvwxyz";
    std::string prog;

private:
    bool is_num(char n);
    bool is_var(char n);
    bool at_eof();
    char read();
    void advance();
    Token scan();
    Token scan_digit();

public:
    auto get_tokens() -> const std::vector<Token>&;
    void set_program(const std::string& s);

};
}
#endif
