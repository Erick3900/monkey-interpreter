#include <gtest/gtest.h>

#include <array>
#include <ranges>
#include <sstream>
#include <algorithm>
#include <cassert>

#include <fmt/format.h>

#include "ast/ast.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

tl::expected<void, std::string> testStatement(arti::monkey::ASTNode *statement, std::string_view identifier);

TEST(parser, let_statements) {
    using namespace arti::monkey;

    auto parser = []{
        constexpr std::string_view input_path = "../tests/parser/let_statements.mnky";

        auto lexer = std::make_unique<Lexer>(input_path);

        return std::make_unique<Parser>(std::move(lexer));
    }();

    auto program_ex = parser->parseProgram();

    if (not program_ex) {
        throw std::runtime_error(program_ex.error());
    }

    auto program = std::move(program_ex).value();

    if(program->statements.size() != 3) {
        EXPECT_EQ(program->statements.size(), 3);
        FAIL();
    }

    constexpr std::array<std::string_view, 3> expectedIdentifiers{
        "x", "y", "foobar"
    };

    for (size_t i = 0; i < expectedIdentifiers.size(); ++i) {
        auto statement = program->statements.at(i);

        auto expected = testStatement(statement, expectedIdentifiers.at(i));

        if (not expected) {
            throw std::runtime_error(expected.error());
        }
    }
}

tl::expected<void, std::string> testStatement(arti::monkey::ASTNode *statement, std::string_view identifier) {
    if (statement == nullptr) {
        return tl::unexpected<std::string>{ "Statement is nullptr" };
    }

    if (statement->tokenLiteral() != "let") {
        return tl::unexpected<std::string>{ fmt::format("Statement 'tokenLiteral' not 'let', got: '{}'", statement->tokenLiteral()) };
    }

    auto letStatement = dynamic_cast<arti::monkey::LetStatement *>(statement);

    if (letStatement == nullptr) {
        return tl::unexpected<std::string>{ "Not a LetStatement" };
    }

    if(not letStatement->name) {
        return tl::unexpected<std::string>{ "LetStatement 'name' is nullptr" };
    }

    if (letStatement->name->value != identifier) {
        return tl::unexpected<std::string>{ fmt::format("LetStatement 'name' not '{}', got: '{}'", identifier, letStatement->name->value) };
    }

    if (letStatement->name->tokenLiteral() != identifier) {
        return tl::unexpected<std::string>{ fmt::format("LetStatement 'tokenLiteral' not '{}', got: '{}'", identifier, letStatement->name->tokenLiteral()) };
    }

    return {};
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
