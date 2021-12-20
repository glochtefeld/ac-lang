#include "catch2/catch.hpp"
#include "scanner/scanner.hpp"

SCENARIO( "The scanner reads tokens appropriately", "[scanner]" ) {
    GIVEN ("A scanner") {
        AC::Scanner s{};

        WHEN ("the program has excessive whitespace") {
            s.set_program("              a                ");
            THEN ("There is only one tokens") {
                auto tokens = s.get_tokens();
                REQUIRE ( tokens.size() == 1 );
                REQUIRE ( tokens[0].type == AC::TokenType::id );
            }
            s.set_program("              a                =                    15.0");
            THEN ("There is only one tokens") {
                auto tokens = s.get_tokens();
                REQUIRE ( tokens.size() == 3 );
                REQUIRE ( tokens[0].type == AC::TokenType::id );
                REQUIRE ( tokens[1].type == AC::TokenType::assign );
                REQUIRE ( tokens[2].type == AC::TokenType::floatdcl );
            }
            s.set_program("              a                +                       6");
            THEN ("There is only one tokens") {
                auto tokens = s.get_tokens();
                REQUIRE ( tokens.size() == 3 );
                REQUIRE ( tokens[0].type == AC::TokenType::id );
                REQUIRE ( tokens[1].type == AC::TokenType::plus );
                REQUIRE ( tokens[2].type == AC::TokenType::intdcl );
            }
        }

        WHEN ( "the program has invalid tokens" ) {
            s.set_program("\\");
            THEN ("the program throws a runtime error") {
                REQUIRE_THROWS( s.get_tokens() );
            }
        }
    }
}
