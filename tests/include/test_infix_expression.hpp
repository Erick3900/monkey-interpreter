#pragma once

#include <string>

#include <fmt/format.h>
#include <tl/expected.hpp>

#include "ast/ast.hpp"

#include "test_literal.hpp"

namespace arti::monkey::testing {

    template <typename LT, typename RT>
    static tl::expected<void, std::string> testInfixExpression(ASTNode *node, std::string_view op, LT lval, RT rval) {
        auto expectedExpression = testExpression(node);

        if (not expectedExpression) {
            return tl::unexpected{ std::move(expectedExpression).error() };
        }

        auto infix = dynamic_cast<InfixExpression *>(expectedExpression.value());

        if (infix == nullptr) {
            return tl::unexpected<std::string>{ fmt::format("ASTNode not an 'InfixExpression', got: '{}'", node->token.type) };
        }

        if (auto expected = testLiteral(infix->left, lval); not expected) {
            return expected;
        }

        if (infix->op != op) {
            return tl::unexpected<std::string>{ fmt::format("Expected InfixExpression with operator '{}', got: '{}'", op, infix->op) };
        }

        if (auto expected = testLiteral(infix->right, rval); not expected) {
            return expected;
        }

        return {};
    }

}
