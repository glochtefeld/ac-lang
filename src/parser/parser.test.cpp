#include "parser/parser.hpp"
#include "../external/catch2/include/catch.hpp"

SCENARIO ( "The parser is given appropriate input" ) {
    GIVEN ( "A parser" ) {
        AC::Parser p{};

        WHEN ( "there are no declarations followed by statements" ) {
            std::vector<AC::Token> toks = {
                AC::Token(AC::TokenType::id,"a"),
                AC::Token(AC::TokenType::assign,""),
                AC::Token(AC::TokenType::id,"b"),
                AC::Token(AC::TokenType::plus,""),
                AC::Token(AC::TokenType::id,"c"),
                AC::Token(AC::TokenType::eof,"")
            };
            p.set_tokens(toks);
            THEN ( "the program is valid" ) {
                REQUIRE ( p.check_program() == true );
            }
        }
        WHEN ( "there are declarations but no statements" ) {
            std::vector<AC::Token> toks = {
                AC::Token(AC::TokenType::floatdcl,"15.0"),
                AC::Token(AC::TokenType::id,"a"),
                AC::Token(AC::TokenType::eof,"")
            };
            p.set_tokens(toks);
            THEN ( "the program is valid" ) {
                REQUIRE ( p.check_program() == true );
            }

        }
        WHEN ( "the program is empty" ) {
            std::vector<AC::Token> toks {AC::Token(AC::TokenType::eof,"")};
            p.set_tokens(toks);
            THEN ( "the program is valid" ) {
                REQUIRE ( p.check_program() == true );
            }
        }
        WHEN ( "there are both declarations and statements" ) {
            std::vector<AC::Token> toks = {
                AC::Token(AC::TokenType::floatdcl,""),
                AC::Token(AC::TokenType::id,"a"),
                AC::Token(AC::TokenType::id,"a"),
                AC::Token(AC::TokenType::assign,""),
                AC::Token(AC::TokenType::fnum,"15.0"),
                AC::Token(AC::TokenType::print,""),
                AC::Token(AC::TokenType::id,"a"),
                AC::Token(AC::TokenType::eof,"")
            };
            p.set_tokens(toks);
            THEN ( "the program is valid" ) {
                REQUIRE ( p.check_program() == true );
            }
        }
        WHEN ( "there are multiple declarations and statements" ) {
            std::vector<AC::Token> toks = {
                AC::Token(AC::TokenType::floatdcl,""),
                AC::Token(AC::TokenType::id,"a"),
                AC::Token(AC::TokenType::intdcl,""),
                AC::Token(AC::TokenType::id,"b"),
                AC::Token(AC::TokenType::id,"a"),
                AC::Token(AC::TokenType::assign,""),
                AC::Token(AC::TokenType::inum,"8"),
                AC::Token(AC::TokenType::id,"b"),
                AC::Token(AC::TokenType::assign,""),
                AC::Token(AC::TokenType::id,"a"),
                AC::Token(AC::TokenType::plus,""),
                AC::Token(AC::TokenType::fnum,"32.8"),
                AC::Token(AC::TokenType::print,""),
                AC::Token(AC::TokenType::id,"b"),
                AC::Token(AC::TokenType::eof,"")
            };
            p.set_tokens(toks);
            THEN ( "the program is valid" ) {
                REQUIRE ( p.check_program() == true );
            }
        }
    }
}

SCENARIO ( "The parser is given a bad program" ) {
    GIVEN ( "A parser" ) {
        AC::Parser p{};
        WHEN ( "declarations are given after statements" ) {
            std::vector<AC::Token> toks = {
                AC::Token(AC::TokenType::print,""),
                AC::Token(AC::TokenType::id,"a"),
                AC::Token(AC::TokenType::plus,""),
                AC::Token(AC::TokenType::inum,"8"),
                AC::Token(AC::TokenType::eof,""),
                AC::Token(AC::TokenType::floatdcl,"15.0"),
                AC::Token(AC::TokenType::id,"a"),
            };
            p.set_tokens(toks);
            THEN ( "the program is invalid" ) {
                REQUIRE ( p.check_program() == false );
            }

        }
        WHEN ( "an assignment has no lhs" ) {
            std::vector<AC::Token> toks = {
                AC::Token(AC::TokenType::assign,""),
                AC::Token(AC::TokenType::id,"b"),
                AC::Token(AC::TokenType::plus,""),
                AC::Token(AC::TokenType::id,"c"),
                AC::Token(AC::TokenType::eof,"")
            };
            p.set_tokens(toks);
            THEN ( "the program is invalid" ) {
                REQUIRE ( p.check_program() == false );
            }
        }
        WHEN ( "an expression is given out of infix form" ) {
            std::vector<AC::Token> toks = {
                AC::Token(AC::TokenType::assign,""),
                AC::Token(AC::TokenType::plus,""),
                AC::Token(AC::TokenType::id,"a"),
                AC::Token(AC::TokenType::id,"b"),
                AC::Token(AC::TokenType::id,"c"),
                AC::Token(AC::TokenType::eof,"")
            };
            p.set_tokens(toks);
            THEN ( "the program is invalid" ) {
                REQUIRE ( p.check_program() == false );
            }
        }
        WHEN ( "there is no eof" ) {
            std::vector<AC::Token> toks = {
                AC::Token(AC::TokenType::assign,""),
                AC::Token(AC::TokenType::plus,""),
                AC::Token(AC::TokenType::id,"a"),
                AC::Token(AC::TokenType::id,"b"),
                AC::Token(AC::TokenType::id,"c"),
            };
            p.set_tokens(toks);
            THEN ( "the program is invalid" ) {
                REQUIRE ( p.check_program() == false );
            }
        }
    }
}
