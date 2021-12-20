#ifndef AC_TOKEN
#define AC_TOKEN
#include <string>
#include <iostream>

namespace AC {
enum class TokenType {
    floatdcl,
    intdcl,
    print,
    id,
    assign,
    plus,
    minus,
    inum,
    fnum,
    blank,
    eof
};

struct Token {
    TokenType type;
    std::string semantic_value;
    Token() : type(TokenType::blank), semantic_value("") {}
    Token(TokenType t, std::string s) : type(t), semantic_value(s) {}
};

inline std::ostream& operator <<(std::ostream& out, const Token& t) {
    auto type = "garbage";
    return out << "Token: type=" << type << ", semantic value="<< t.semantic_value;
}
}   
#endif
