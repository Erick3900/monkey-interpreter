#include <gtest/gtest.h>

#include <array>
#include <ranges>
#include <sstream>
#include <algorithm>
#include <cassert>

#include "lexer/lexer.hpp"
#include "ast/ast.hpp"
#include "parser/parser.hpp"

tl::expected<void, std::string> testStatement(arti::monkey::ASTNode *statement);

TEST(parser, return_statements) {
    using namespace arti::monkey;

    auto parser = []{
        constexpr std::string_view input_path = "../tests/parser/return_statements.mnky";

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

    for (auto statement : program->statements) {
        auto expected = testStatement(statement);

        if (not expected) {
            throw std::runtime_error(expected.error());
        }
    }
}

tl::expected<void, std::string> testStatement(arti::monkey::ASTNode *statement) {
    if (statement == nullptr) {
        return tl::unexpected<std::string>{ "Statement is nullptr" };
    }

    if (statement->tokenLiteral() != "return") {
        return tl::unexpected<std::string>{ fmt::format("Statement 'tokenLiteral' not 'return', got: '{}'", statement->tokenLiteral()) };
    }

    auto returnStatement = dynamic_cast<arti::monkey::ReturnStatement *>(statement);

    if (returnStatement == nullptr) {
        return tl::unexpected<std::string>{ "Not a ReturnStatement" };
    }

    return {};
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
