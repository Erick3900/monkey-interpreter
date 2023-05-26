#pragma once

#include <string>
#include <iostream>

#include <tl/expected.hpp>

#include "ast/ast.hpp"

#include "test_expression.hpp"
#include "test_literal.hpp"

namespace arti::monkey::testing {

    template <typename T>
    static tl::expected<void, std::string> testLiteralExpression(ASTNode *node, T expected) {
        auto expectedExpression = testExpression(node);

        if (not expectedExpression) {
            return tl::unexpected{ std::move(expectedExpression).error() };
        }

        return testLiteral(expectedExpression.value(), expected);
    }

}
