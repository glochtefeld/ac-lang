#include "parser/parser.hpp"
using namespace AC;

inline auto Parser::read()->Token {
    return tokens[pos];
}

inline bool Parser::match(const Token& tok, TokenType type) {
    return tok.type == type;
}

bool Parser::multi_match(const Token& tok, const std::vector<TokenType>& types) {
    return std::find(begin(types),end(types),tok.type) != std::end(types);
}
    

inline void Parser::advance() { pos++; };

void Parser::throw_err(const std::string& s) {
    throw std::runtime_error(s);
}

void Parser::expect(const std::string& s, TokenType t) {
    auto tok = read();
    if (!match(tok,t)) {
        std::string e = "ERR: expected " + s + ". Found " + type_print(tok.type);
        throw_err(e.c_str());
    }
    if (!match(tok,TokenType::eof))
        advance();
}

void Parser::prog() {
    std::vector<TokenType> matches{
        TokenType::floatdcl, 
        TokenType::intdcl,
        TokenType::id,
        TokenType::print};

    if (multi_match(read(),matches)) {
        dcls();
        stmts();
        expect("{$}",TokenType::eof);
    }
    else { // see #prog_check
        expect("{$,float,int}",TokenType::eof);
    }
}

void Parser::dcls() {
    auto t = read();
    std::vector<TokenType> matches {
        TokenType::floatdcl,
        TokenType::intdcl};
    if (multi_match(t,matches)) {
        dcl();
        dcls();
    }
    else { 
        matches = {TokenType::id, TokenType::print, TokenType::eof};
        if (!multi_match(t,matches)) 
            throw_err("Expected lambda to resolve as Stmts");
    }
}
void Parser::dcl() {
    auto t = read();
    if (match(t,TokenType::floatdcl)) {
        advance();
        expect("{id}",TokenType::id);
    }
    else if (match(t,TokenType::intdcl)) {
        advance();
        expect("{id}",TokenType::id);
    }
}

void Parser::stmts() {
    std::vector<TokenType> matches {
        TokenType::id,
        TokenType::print};
    if (multi_match(read(),matches)) {
            stmt();
            stmts();
    }
    else {
        expect("{$}",TokenType::eof);
    }
}
void Parser::stmt() {
    auto t = read();
    if (match(t,TokenType::id)) {
        advance();
        expect("{assign}",TokenType::assign);
        val();
        expr();
    }
    else if (match(t,TokenType::print)) {
        advance();
        expect("{id}",TokenType::id);
    }
}
void Parser::expr() {
    auto t = read();
    std::vector<TokenType> matches {
        TokenType::plus,
        TokenType::minus};
    if (match(t,TokenType::plus)) {
        advance();
        val();
        expr();
    }
    else if (match(t,TokenType::minus)) {
        advance();
        val();
        expr();
    }
    else {
        matches = {TokenType::id, TokenType::print, TokenType::eof};
        if (!multi_match(t,matches))
            throw_err("Expected {id, print}");
    }
}
void Parser::val() {
    auto t = read();
    if (match(t,TokenType::id)) {
        advance();
    }
    else if (match(t,TokenType::inum)) {
        advance();
    }
    else if (match(t,TokenType::fnum)) {
        advance();
    }
    else {
        throw_err("Val expected {id,inum,fnum}.");
    }
}

void Parser::set_tokens(const std::vector<Token>& t) {
    tokens = t;
    pos = 0;
    ast = Tree{};
}

bool Parser::check_program() {
    try {
        prog();
        return true;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return false;
    }
}
