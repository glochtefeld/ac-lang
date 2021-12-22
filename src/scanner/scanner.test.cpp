#include "../external/catch2/catch.hpp"
#include "scanner/scanner.hpp"

SCENARIO ( "The scanner reads tokens appropriately", "[scanner]" ) {
    GIVEN ("A scanner") {
        AC::Scanner s{};

        WHEN ("the program is an empty file (which it is by default)") {
            s.set_program("");
            THEN ("There is still one token, an EOF") {
                auto tokens = s.get_tokens();
                REQUIRE ( tokens.size() == 1);
                REQUIRE ( tokens[0].type == AC::TokenType::eof );
            }
        }
        WHEN ("the program has excessive whitespace") {
            s.set_program("        4  ");
            THEN ("The token is still parsed") {
                auto tokens = s.get_tokens();
                REQUIRE ( tokens.size() == 2 );
                REQUIRE ( tokens[0].type == AC::TokenType::inum );
            }
            s.set_program("              a                =                    15.0");
            THEN ("There are four tokens: id, assign, floatdcl, and EOF") {
                auto tokens = s.get_tokens();
                REQUIRE ( tokens.size() == 4 );
                REQUIRE ( tokens[0].type == AC::TokenType::id );
                REQUIRE ( tokens[1].type == AC::TokenType::assign );
                REQUIRE ( tokens[2].type == AC::TokenType::fnum );
            }
        }
        WHEN ( "the program has invalid tokens" ) {
            s.set_program("$");
            THEN ("the program throws a runtime error") {
                REQUIRE_THROWS( s.get_tokens() );
            }
        }
        WHEN ( "the program has no whitespace" ) {
            s.set_program("a=0");
            THEN ("tokens are still read individually") {
                auto tokens = s.get_tokens();
                REQUIRE ( tokens.size() == 4 );
                REQUIRE ( tokens[0].type == AC::TokenType::id );
                REQUIRE ( tokens[1].type == AC::TokenType::assign );
                REQUIRE ( tokens[2].type == AC::TokenType::inum );
            }
        }
        WHEN ( "ints and floats are in the same program" ) {
            s.set_program("15 33.093");
            THEN ("the tokens are separated and the value is stored") {
                auto tokens = s.get_tokens();
                REQUIRE ( tokens.size() == 3 );
                REQUIRE ( tokens[0].type == AC::TokenType::inum );
                REQUIRE ( tokens[0].semantic_value == "15" );
                REQUIRE ( tokens[1].type == AC::TokenType::fnum );
                REQUIRE ( tokens[1].semantic_value == "33.093" );
            }
        }
    }
}
