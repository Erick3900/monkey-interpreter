#include <gtest/gtest.h>

#include <array>
#include <ranges>
#include <sstream>
#include <algorithm>
#include <cassert>

#include "lexer/lexer.hpp"
#include "ast/ast.hpp"
#include "parser/parser.hpp"

TEST(parser, identifier_expression) {
    using namespace arti::monkey;

    auto parser = []{
        constexpr std::string_view input_path = "../tests/parser/identifier_expression.mnky";

        auto lexer = std::make_unique<Lexer>(input_path);

        return std::make_unique<Parser>(std::move(lexer));
    }();

    auto program_ex = parser->parseProgram();

    if (not program_ex) {
        throw std::runtime_error(program_ex.error());
    }

    auto program = std::move(program_ex).value();

    if(program->statements.size() != 1) {
        EXPECT_EQ(program->statements.size(), 1);
        FAIL();
    }

    auto statement = dynamic_cast<ExpressionStatement *>(program->statements[0]);

    if (statement == nullptr) {
        throw std::runtime_error(fmt::format("Not a 'ExpressionStatement'"));
    }

    auto identifier = dynamic_cast<Identifier *>(statement->expression);

    if (identifier == nullptr) {
        throw std::runtime_error(fmt::format("Not a 'Identifier'"));
    }

    EXPECT_EQ(identifier->value, "foobar");
    EXPECT_EQ(identifier->tokenLiteral(), "foobar");
}

TEST(parser, integer_literal_expression) {
    using namespace arti::monkey;

    auto parser = []{
        constexpr std::string_view input_path = "../tests/parser/integer_literal_expression.mnky";

        auto lexer = std::make_unique<Lexer>(input_path);

        return std::make_unique<Parser>(std::move(lexer));
    }();

    auto program_ex = parser->parseProgram();

    if (not program_ex) {
        throw std::runtime_error(program_ex.error());
    }

    auto program = std::move(program_ex).value();

    if(program->statements.size() != 1) {
        EXPECT_EQ(program->statements.size(), 1);
        FAIL();
    }

    auto statement = dynamic_cast<ExpressionStatement *>(program->statements[0]);

    if (statement == nullptr) {
        throw std::runtime_error(fmt::format("Not a 'ExpressionStatement'"));
    }

    auto literal = dynamic_cast<IntegerLiteral *>(statement->expression);

    if (literal == nullptr) {
        throw std::runtime_error(fmt::format("Not a 'IntegerLiteral'"));
    }

    EXPECT_EQ(literal->value, 5);
    EXPECT_EQ(literal->tokenLiteral(), "5");
}

TEST(parser, prefix_expression) {
    using namespace arti::monkey;

    constexpr std::array<std::pair<std::string_view, int64_t>, 2> expectedPrefixes{
        std::pair{ "!", 5 },
        std::pair{ "-", 15 },
    };

    auto parser = []{
        constexpr std::string_view input_path = "../tests/parser/prefix_expression.mnky";

        auto lexer = std::make_unique<Lexer>(input_path);

        return std::make_unique<Parser>(std::move(lexer));
    }();

    auto program_ex = parser->parseProgram();

    if (not program_ex) {
        throw std::runtime_error(program_ex.error());
    }

    auto program = std::move(program_ex).value();

    if(program->statements.size() != expectedPrefixes.size()) {
        EXPECT_EQ(program->statements.size(), expectedPrefixes.size());
        FAIL();
    }

    auto testIntegerLiteral = [] (ASTNode *node, int64_t value) {
        auto literal = dynamic_cast<IntegerLiteral *>(node);

        if (literal == nullptr) {
            throw std::runtime_error(fmt::format("Not a 'IntegerLiteral'"));
        }

        EXPECT_EQ(literal->value, value);
        EXPECT_EQ(literal->tokenLiteral(), fmt::to_string(value));
    };

    auto checkPrefixStatement = [&testIntegerLiteral](ExpressionStatement *statement, std::string_view op, int64_t val) {
        auto prefix= dynamic_cast<PrefixExpression *>(statement->expression);

        if (prefix == nullptr) {
            throw std::runtime_error(fmt::format("Not a 'PrefixExpression'"));
        }

        ASSERT_EQ(prefix->op, op);
        testIntegerLiteral(prefix->right, val);
    };

    for (size_t i = 0; i < expectedPrefixes.size(); ++i) {
        auto statement = dynamic_cast<ExpressionStatement *>(program->statements[i]);

        if (statement == nullptr) {
            throw std::runtime_error(fmt::format("Not a 'ExpressionStatement'"));
        }

        auto [op, val] = expectedPrefixes[i];
        checkPrefixStatement(statement, op, val);
    }
}

TEST(parser, infix_expression) {
    using namespace arti::monkey;

    struct ExpectedInfixExpression {
        int64_t lValue;
        int64_t rValue;
        std::string_view op;
    };

    constexpr std::array<ExpectedInfixExpression, 8> expectedInfixes{
        ExpectedInfixExpression{ 5, 5, "+" },
        ExpectedInfixExpression{ 5, 5, "-" },
        ExpectedInfixExpression{ 5, 5, "*" },
        ExpectedInfixExpression{ 5, 5, "/" },
        ExpectedInfixExpression{ 5, 5, ">" },
        ExpectedInfixExpression{ 5, 5, "<" },
        ExpectedInfixExpression{ 5, 5, "==" },
        ExpectedInfixExpression{ 5, 5, "!=" },
    };

    auto parser = []{
        constexpr std::string_view input_path = "../tests/parser/infix_expression.mnky";

        auto lexer = std::make_unique<Lexer>(input_path);

        return std::make_unique<Parser>(std::move(lexer));
    }();

    auto program_ex = parser->parseProgram();

    if (not program_ex) {
        throw std::runtime_error(program_ex.error());
    }

    auto program = std::move(program_ex).value();

    if(program->statements.size() != expectedInfixes.size()) {
        EXPECT_EQ(program->statements.size(), expectedInfixes.size());
        FAIL();
    }

    auto testIntegerLiteral = [] (ASTNode *node, int64_t value) {
        auto literal = dynamic_cast<IntegerLiteral *>(node);

        if (literal == nullptr) {
            throw std::runtime_error(fmt::format("Not a 'IntegerLiteral'"));
        }

        EXPECT_EQ(literal->value, value);
        EXPECT_EQ(literal->tokenLiteral(), fmt::to_string(value));
    };

    auto checkPrefixStatement = [&testIntegerLiteral](ExpressionStatement *statement, std::string_view op, int64_t lval, int64_t rval) {
        auto infix= dynamic_cast<InfixExpression *>(statement->expression);

        if (infix == nullptr) {
            throw std::runtime_error(fmt::format("Not a 'InfixExpression'"));
        }

        ASSERT_EQ(infix->op, op);
        testIntegerLiteral(infix->left, lval);
        testIntegerLiteral(infix->right, rval);
    };

    for (size_t i = 0; i < expectedInfixes.size(); ++i) {
        auto statement = dynamic_cast<ExpressionStatement *>(program->statements[i]);

        if (statement == nullptr) {
            throw std::runtime_error(fmt::format("Not a 'ExpressionStatement'"));
        }

        auto [lval, rval, op] = expectedInfixes[i];
        checkPrefixStatement(statement, op, lval, rval);
    }
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
