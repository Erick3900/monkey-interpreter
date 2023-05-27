#include "ast/types/expression_statement.hpp"

#include <string>

namespace arti::monkey {

    ExpressionStatement::ExpressionStatement()
        : expression(nullptr) { }

    std::string ExpressionStatement::toString() const {
        if (expression) {
            return expression->toString();
        }

        return "";
    }

}    // namespace arti::monkey
