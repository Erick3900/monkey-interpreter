#include "ast/types/infix_expression.hpp"

#include <sstream>

namespace arti::monkey {

    InfixExpression::InfixExpression()
        : left(nullptr)
        , right(nullptr)
        , op{} { }

    std::string InfixExpression::toString() const {
        std::stringstream ss;

        ss << "(" << left->toString() << " " << op << " " << right->toString() << ")";

        return ss.str();
    }

}    // namespace arti::monkey
