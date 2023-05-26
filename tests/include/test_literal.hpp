#pragma once

#include <string>
#include <iostream>

#include <tl/expected.hpp>

#include "ast/ast.hpp"

#include "test_expression.hpp"
#include "test_identifier.hpp"
#include "test_integer_literal.hpp"
#include "test_boolean_literal.hpp"

namespace arti::monkey::testing {

    template <typename T>
    static tl::expected<void, std::string> testLiteral(ASTNode *node, T expected) {
        if constexpr (std::is_same_v<bool, T>) {
            return testBooleanLiteral(node, expected);
        }
        if constexpr (std::is_integral_v<T>) {
            return testIntegerLiteral(node, expected);
        }
        else if constexpr (std::is_constructible_v<std::string_view, T>) {
            return testIdentifier(node, expected);
        }
        else {
            static_assert("Unexpected type for testing");
        }
    }

}
