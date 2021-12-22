#ifndef AC_PARSER
#define AC_PARSER
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream> // Remove after tests are written, this is for helpful debuggery
#include "scanner/token.hpp"
#include "ast/tree.hpp"

namespace AC {
class Parser {
private:
    unsigned int pos{};
    std::vector<Token> tokens{};
    Tree ast{};

private: // Generic parser methods
    auto read()->Token;
    bool match(const Token&, TokenType);
    bool multi_match(const Token&, const std::vector<TokenType>&);
    void advance();
    void expect(const std::string&, TokenType);
    void throw_err(const std::string&);

private: // AC specific methods
    void prog();
    void dcls();
    void dcl();
    void stmts();
    void stmt();
    void expr();
    void val();
public:
    void set_tokens(const std::vector<Token>&);
    bool check_program();
    auto get_AST()->Tree&;
};
}
#endif
