#pragma once

#include <string>

#include <fmt/format.h>
#include <tl/expected.hpp>

#include "ast/ast.hpp"

#include "test_literal.hpp"

namespace arti::monkey::testing {

    template <typename T>
    static tl::expected<void, std::string> testPrefixExpression(ASTNode *node, std::string_view op, T value) {
        auto expectedExpression = testExpression(node);

        if (not expectedExpression) {
            return tl::unexpected{ std::move(expectedExpression).error() };
        }

        auto prefix = dynamic_cast<PrefixExpression *>(expectedExpression.value());

        if (prefix == nullptr) {
            return tl::unexpected<std::string>{ fmt::format("ASTNode not an 'PrefixExpression', got: '{}'", node->token.type) };
        }

        if (prefix->op != op) {
            return tl::unexpected<std::string>{ fmt::format("Expected PrefixExpression with operator '{}', got: '{}'", op, prefix->op) };
        }

        if (auto expected = testLiteral(prefix->right, value); not expected) {
            return expected;
        }

        return {};
    }

}
