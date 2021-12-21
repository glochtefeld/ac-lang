#include "scanner/scanner.hpp"
inline bool AC::Scanner::at_eof() {
    return cur_pos >= prog.size();
}

inline char AC::Scanner::read() {
    return prog[cur_pos];
}

void AC::Scanner::set_program(const std::string& s) {
    prog = s;
    cur_pos = 0;
    tokens.clear();
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
    while (read() == ' ')
        advance();

    Token t{};
    if ( at_eof() )
        t.type = TokenType::eof;
    else {
        const auto current = read();
        if (is_num(current))
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
                    std::string err = "Error: unknown character " + std::string(&current) + ", ascii " + std::to_string((int)current);
                    throw std::runtime_error(err);
            }
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

auto AC::Scanner::get_tokens() -> const std::vector<AC::Token>& {
    do {
        auto t = scan();
        tokens.push_back(t);
    }
    while ( !at_eof() );
    if (tokens.back().type != TokenType::eof)
        tokens.push_back(Token(TokenType::eof,""));
    return tokens;
}
