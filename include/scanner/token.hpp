#ifndef AC_TOKEN
#define AC_TOKEN
#include "../external/magic_enum/include/magic_enum.hpp"
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

inline std::string type_print(TokenType t) {
    switch (t) {
    case TokenType::floatdcl:
        return "floatdcl";
    case TokenType::intdcl:
        return "intdcl";
    case TokenType::print:
        return "print";
    case TokenType::id:
        return "id";
    case TokenType::assign:
        return "assign";
    case TokenType::plus:
        return "plus";
    case TokenType::minus:
        return "minus";
    case TokenType::inum:
        return "inum";
    case TokenType::fnum:
        return "fnum";
    case TokenType::blank:
        return "blank";
    case TokenType::eof:
        return "eof";
    default:
        return "";
    }
}

struct Token {
    TokenType type;
    std::string semantic_value;
    Token() : type(TokenType::blank), semantic_value("") {}
    Token(TokenType t, std::string s) : type(t), semantic_value(s) {}
};

inline auto operator<<(std::ostream& out, const Token& t)-> std::ostream& {
    return out << "Token(type="  << type_print(t.type) << ",val=" << t.semantic_value;
}
}
#endif
