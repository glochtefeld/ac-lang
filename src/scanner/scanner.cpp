#include "scanner/scanner.hpp"
inline char AC::Scanner::peek() {
    return cur_pos+1>prog.length() ? 0 : prog[cur_pos+1];
}

inline char AC::Scanner::read() {
    return prog[cur_pos];
}

void AC::Scanner::set_program(const std::string& s) {
    prog = s;
}

inline void AC::Scanner::advance() {
    cur_pos++;
}

bool AC::Scanner::is_num(char n) {
    return nums.find(n) != std::string::npos;
}

bool AC::Scanner::is_var(char n) {
    return letters.find(n) != std::string::npos;
}

AC::Token AC::Scanner::scan() {
    Token t{};
    while (read() == ' ')
        advance();
    const auto current = read();
    const auto next = peek();
    if (next == 0) 
        t.type = TokenType::eof;
    else if (is_num(current))
        t = scan_digit();
    else if (is_var(current)) {
        t.type = TokenType::id;
        t.semantic_value = std::string(&current);
    }
    else {
        switch (current) {
            case 'f':
                t.type = TokenType::floatdcl;
                break;
            case 'i':
                t.type =TokenType::intdcl;
                break;
            case 'p':
                t.type = TokenType::print;
                break;
            case '+':
                t.type = TokenType::plus;
                break;
            case '-':
                t.type = TokenType::minus;
                break;
            case '=':
                t.type = TokenType::assign;
                break;
            default:
                std::string err = "Error: unknown character " + current;
                throw std::runtime_error(err);
        }
    }
    advance();
    return t;
}

AC::Token AC::Scanner::scan_digit() {
    Token t{};
    while (is_num(read())) {
        t.semantic_value += read();
        advance();
    }
    if (read() != '.') 
        t.type = TokenType::intdcl;
    else {
        t.semantic_value += read();
        advance();
        while (is_num(read())) {
            t.semantic_value += read();
            advance();
        }
        t.type = TokenType::floatdcl;
    }
    return t;
}

std::vector<AC::Token> AC::Scanner::get_tokens() {
    while (cur_pos < prog.length()) {
        auto t = scan();
        tokens.push_back(t);
    }
    return tokens;
}
