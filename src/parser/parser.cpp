#include "parser/parser.hpp"
using namespace AC;

inline auto Parser::read()->Token {
    return tokens[pos];
}

inline auto Parser::peek()->Token {
    return tokens[pos+1];
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
    if (!match(read(),t)) {
        std::string e = "ERR: expected " + s + ". Found " + type_print(read().type);
        throw_err(e);
    }
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
    std::vector<TokenType> matches {
        TokenType::floatdcl,
        TokenType::intdcl};
    if (multi_match(read(),matches)) {
        dcl();
        dcls();
    }
    else { // see #prog_check
        expect("{$,float,int}",TokenType::eof);
    }
}
void Parser::dcl() {
    if (match(read(),TokenType::floatdcl)) {
        advance();
        expect("{id}",TokenType::id);
    }
    else if (match(read(),TokenType::intdcl)) {
        advance();
        expect("{id}",TokenType::id);
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
    

/* Comments
 * #prog_check: In the book, the pseudocode checks for an EOF and does nothing,
 * and then failing that errors out. This is a minor restructure which errors after
 * not reading an EOF.
 *
 */
