#include <gtest/gtest.h>

#include <array>
#include <ranges>
#include <sstream>
#include <algorithm>
#include <cassert>

#include "ast/ast.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "token/token_definitions.hpp"

TEST(ast, to_string) {
    using namespace arti::monkey;

    Identifier myVar;
    myVar.token = Token{
        .type = tokens::Ident.type,
        .literal = "myVar"
    };
    myVar.value = myVar.token.literal;

    Identifier anotherVar;
    anotherVar.token = Token{
        .type = tokens::Ident.type,
        .literal = "anotherVar"
    };
    anotherVar.value = anotherVar.token.literal;

    LetStatement mainStatement;
    mainStatement.token = Token{
        .type = tokens::Let.type,
        .literal = "let"
    };
    mainStatement.name = &myVar;
    mainStatement.value = &anotherVar;

    Program p;
    p.statements.push_back(&mainStatement);

    EXPECT_EQ(p.toString(), "let myVar = anotherVar;");
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
