#include <gtest/gtest.h>

#include <array>
#include <ranges>
#include <sstream>
#include <algorithm>
#include <cassert>

#include "lexer/lexer.hpp"

TEST(lexer, next_token) {
    using namespace arti::monkey;

    const std::array<Token, 74> expected_tokens{
        Token{ tokens::Let.type, "let" },
        Token{ tokens::Ident.type, "five" },
        Token{ tokens::Assign.type, "=" },
        Token{ tokens::Int.type, "5" },
        Token{ tokens::Semicolon.type, ";" },

        Token{ tokens::Let.type, "let" },
        Token{ tokens::Ident.type, "ten" },
        Token{ tokens::Assign.type, "=" },
        Token{ tokens::Int.type, "10" },
        Token{ tokens::Semicolon.type, ";" },
 
        Token{ tokens::Let.type, "let" },
        Token{ tokens::Ident.type, "add" },
        Token{ tokens::Assign.type, "=" },
        Token{ tokens::Function.type, "fn" },
        Token{ tokens::LParen.type, "(" },
        Token{ tokens::Ident.type, "x" },
        Token{ tokens::Comma.type, "," },
        Token{ tokens::Ident.type, "y" },
        Token{ tokens::RParen.type, ")" },
        Token{ tokens::LSquirly.type, "{" },
        Token{ tokens::Ident.type, "x" },
        Token{ tokens::Plus.type, "+" },
        Token{ tokens::Ident.type, "y" },
        Token{ tokens::Semicolon.type, ";" },
        Token{ tokens::RSquirly.type, "}" },
        Token{ tokens::Semicolon.type, ";" },

        Token{ tokens::Let.type, "let" },
        Token{ tokens::Ident.type, "result" },
        Token{ tokens::Assign.type, "=" },
        Token{ tokens::Ident.type, "add" },
        Token{ tokens::LParen.type, "(" },
        Token{ tokens::Ident.type, "five" },
        Token{ tokens::Comma.type, "," },
        Token{ tokens::Ident.type, "ten" },
        Token{ tokens::RParen.type, ")" },
        Token{ tokens::Semicolon.type, ";" },

        Token{ tokens::Bang.type, "!" },
        Token{ tokens::Minus.type, "-" },
        Token{ tokens::Slash.type, "/" },
        Token{ tokens::Asterisk.type, "*" },
        Token{ tokens::Int.type, "5" },
        Token{ tokens::Semicolon.type, ";" },

        Token{ tokens::Int.type, "5" },
        Token{ tokens::Lt.type, "<" },
        Token{ tokens::Int.type, "10" },
        Token{ tokens::Gt.type, ">" },
        Token{ tokens::Int.type, "5" },
        Token{ tokens::Semicolon.type, ";" },

        Token{ tokens::If.type, "if" },
        Token{ tokens::LParen.type, "(" },
        Token{ tokens::Int.type, "5" },
        Token{ tokens::Lt.type, "<" },
        Token{ tokens::Int.type, "10" },
        Token{ tokens::RParen.type, ")" },
        Token{ tokens::LSquirly.type, "{" },
        Token{ tokens::Return.type, "return" },
        Token{ tokens::True.type, "true" },
        Token{ tokens::Semicolon.type, ";" },
        Token{ tokens::RSquirly.type, "}" },

        Token{ tokens::Else.type, "else" },
        Token{ tokens::LSquirly.type, "{" },
        Token{ tokens::Return.type, "return" },
        Token{ tokens::False.type, "false" },
        Token{ tokens::Semicolon.type, ";" },
        Token{ tokens::RSquirly.type, "}" },

        Token{ tokens::Int.type, "10" },
        Token{ tokens::Eq.type, "==" },
        Token{ tokens::Int.type, "10" },
        Token{ tokens::Semicolon.type, ";" },

        Token{ tokens::Int.type, "10" },
        Token{ tokens::Ne.type, "!=" },
        Token{ tokens::Int.type, "9" },
        Token{ tokens::Semicolon.type, ";" },

        Token{ tokens::EOF.type, "" }
    };

    auto lexer = Lexer{ "../tests/lexer/next_token.mnky" };
    auto tokensIter = lexer.begin();

    std::ranges::for_each(
        expected_tokens,
        [&](const auto &expected_token) {
            EXPECT_NE(tokensIter, lexer.end());

            auto token = *tokensIter;
            ++tokensIter;

            EXPECT_EQ(expected_token.type, token.type);
            EXPECT_EQ(expected_token.literal, token.literal);
        }
    );

    EXPECT_EQ(tokensIter, lexer.end());
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
