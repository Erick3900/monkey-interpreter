#include <gtest/gtest.h>

#include <array>
#include <ranges>
#include <sstream>
#include <algorithm>
#include <cassert>

#include "lexer/lexer.hpp"
#include "ast/ast.hpp"
#include "parser/parser.hpp"

#include "test_infix_expression.hpp"
#include "test_prefix_expression.hpp"
#include "test_literal_expression.hpp"

namespace tests = arti::monkey::testing;

TEST(parser, identifier_expression) {
    using namespace arti::monkey;

    constexpr std::array<std::string_view, 1> expectedIdentifiers{
        "foobar"
    };

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

    if(program->statements.size() != expectedIdentifiers.size()) {
        EXPECT_EQ(program->statements.size(), expectedIdentifiers.size());
        FAIL();
    }

    for (size_t i = 0; i < expectedIdentifiers.size(); ++i) {
        auto node = program->statements.at(i);
        auto expIdentifier = expectedIdentifiers.at(i);

        if (auto isExpression = tests::testExpression(node); isExpression) {
            node = isExpression.value();

            auto expectedOk = tests::testIdentifier(node, expIdentifier);

            if (not expectedOk) {
                throw std::runtime_error(expectedOk.error());
            }
        }
        else {
            throw std::runtime_error(isExpression.error());
        }
    }
}

TEST(parser, integer_literal_expression) {
    using namespace arti::monkey;

    constexpr std::array<int64_t, 1> expectedIntegers{
        5
    };

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

    if(program->statements.size() != expectedIntegers.size()) {
        EXPECT_EQ(program->statements.size(), expectedIntegers.size());
        FAIL();
    }

    for (size_t i = 0; i < expectedIntegers.size(); ++i) {
        auto node = program->statements.at(0);
        auto expInt = expectedIntegers.at(0);

        if (auto isExpression = tests::testExpression(node); isExpression) {
            node = isExpression.value();

            auto expectedOk = tests::testIntegerLiteral(node, expInt);

            if (not expectedOk) {
                throw std::runtime_error(expectedOk.error());
            }
        }
        else {
            throw std::runtime_error(isExpression.error());
        }
    }
}

TEST(parser, prefix_expression) {
    using namespace arti::monkey;

    struct ExpectedPrefix {
        std::string_view op;
        std::variant<std::string_view, int64_t, bool> value;
    };

    constexpr std::array<ExpectedPrefix, 4> expectedPrefixes{
        ExpectedPrefix{ "!", 5 },
        ExpectedPrefix{ "-", 15 },
        ExpectedPrefix{ "!", true },
        ExpectedPrefix{ "!", false },
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

    for (size_t i = 0; i < expectedPrefixes.size(); ++i) {
        auto node = program->statements.at(i);
        auto [op, val] = expectedPrefixes.at(i);

        tl::expected<void, std::string> expectedOk;

        if (std::holds_alternative<int64_t>(val)) {
            expectedOk = tests::testPrefixExpression(node, op, std::get<int64_t>(val));
        }
        else if (std::holds_alternative<std::string_view>(val)) {
            expectedOk = tests::testPrefixExpression(node, op, std::get<std::string_view>(val));
        }
        else if (std::holds_alternative<bool>(val)) {
            expectedOk = tests::testPrefixExpression(node, op, std::get<bool>(val));
        }

        if (not expectedOk) {
            throw std::runtime_error(expectedOk.error());
        }
    }
}

TEST(parser, infix_expression) {
    using namespace arti::monkey;

    struct ExpectedInfixExpression {
        std::variant<std::string_view, int64_t, bool> lValue;
        std::variant<std::string_view, int64_t, bool> rValue;
        std::string_view op;
    };

    constexpr std::array<ExpectedInfixExpression, 11> expectedInfixes{
        ExpectedInfixExpression{ 5, 5, "+" },
        ExpectedInfixExpression{ 5, 5, "-" },
        ExpectedInfixExpression{ 5, 5, "*" },
        ExpectedInfixExpression{ 5, 5, "/" },
        ExpectedInfixExpression{ 5, 5, ">" },
        ExpectedInfixExpression{ 5, 5, "<" },
        ExpectedInfixExpression{ 5, 5, "==" },
        ExpectedInfixExpression{ 5, 5, "!=" },
        ExpectedInfixExpression{ true, true, "==" },
        ExpectedInfixExpression{ true, false, "!=" },
        ExpectedInfixExpression{ false, false, "==" }
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

    for (size_t i = 0; i < expectedInfixes.size(); ++i) {
        auto node = program->statements.at(i);
        auto [lval, rval, op] = expectedInfixes[i];

        tl::expected<void, std::string> expectedOk;

        if (std::holds_alternative<int64_t>(lval)) {
            if (std::holds_alternative<int64_t>(rval)) {
                expectedOk = tests::testInfixExpression(node, op, std::get<int64_t>(lval), std::get<int64_t>(rval));
            }
            else if (std::holds_alternative<std::string_view>(rval)) {
                expectedOk = tests::testInfixExpression(node, op, std::get<int64_t>(lval), std::get<std::string_view>(rval));
            }
            else if (std::holds_alternative<bool>(rval)) {
                expectedOk = tests::testInfixExpression(node, op, std::get<int64_t>(lval), std::get<bool>(rval));
            }
        }
        else if (std::holds_alternative<std::string_view>(lval)) {
            if (std::holds_alternative<int64_t>(rval)) {
                expectedOk = tests::testInfixExpression(node, op, std::get<std::string_view>(lval), std::get<int64_t>(rval));
            }
            else if (std::holds_alternative<std::string_view>(rval)) {
                expectedOk = tests::testInfixExpression(node, op, std::get<std::string_view>(lval), std::get<std::string_view>(rval));
            }
            else if (std::holds_alternative<bool>(rval)) {
                expectedOk = tests::testInfixExpression(node, op, std::get<std::string_view>(lval), std::get<bool>(rval));
            }
        }
        else if (std::holds_alternative<bool>(lval)) {
            if (std::holds_alternative<int64_t>(rval)) {
                expectedOk = tests::testInfixExpression(node, op, std::get<bool>(lval), std::get<int64_t>(rval));
            }
            else if (std::holds_alternative<std::string_view>(rval)) {
                expectedOk = tests::testInfixExpression(node, op, std::get<bool>(lval), std::get<std::string_view>(rval));
            }
            else if (std::holds_alternative<bool>(rval)) {
                expectedOk = tests::testInfixExpression(node, op, std::get<bool>(lval), std::get<bool>(rval));
            }
        }

        if (not expectedOk) {
            throw std::runtime_error(expectedOk.error());
        }
    }
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
