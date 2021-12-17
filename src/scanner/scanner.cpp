#include "scanner/scanner.hpp"
char AC::Scanner::peek() {
    return cur_pos+1>prog.length() ? 0 : prog[cur_pos+1];
}

void AC::Scanner::set_program(const std::string& s) {
    prog = s;
}

void AC::Scanner::advance() {
    cur_pos++;
}

bool AC::Scanner::is_num(char n) {
    return nums.find(n) != std::string::npos;
}

bool AC::Scanner::is_var(char n) {
    return letters.find(n) != std::string::npos;
}

AC::Token AC::Scanner::scan() {
    while (prog[cur_pos] == ' ')
        advance();
    auto c = prog[cur_pos];
    advance();
    if (c == 0)
        return Token(TokenType::eof, "");
    else if (is_num(peek()))
        return scan_digit();
    else if (is_var(c))
        return Token(TokenType::id, std::string(&c));
    else {
        switch (c) {
            case 'f':
                return Token(TokenType::floatdcl, "");
            case 'i':
                return Token(TokenType::intdcl, "");
            case 'p':
                return Token(TokenType::print, "");
            case '+':
                return Token(TokenType::plus, "");
            case '-':
                return Token(TokenType::minus, "");
            case '=':
                return Token(TokenType::assign, "");
            default:
                return Token(TokenType::eof,"");
        }
    }
}

AC::Token AC::Scanner::scan_digit() {
    std::string val = "";
    while (is_num(peek())) {
        val += prog[cur_pos];
        advance();
    }
    if (peek() != '.') 
        return Token(TokenType::intdcl,val);
    else {
        advance();
        val += prog[cur_pos];
        while (is_num(peek())) {
            val += prog[cur_pos];
            advance();
        }
        return Token(TokenType::floatdcl, val);
    }
}

std::vector<AC::Token> AC::Scanner::get_tokens() {
    while (cur_pos < prog.length()) {
        auto t = scan();
        tokens.push_back(t);
    }
    return tokens;
}
