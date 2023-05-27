#include "ast/types/prefix_expression.hpp"

#include <sstream>

namespace arti::monkey {

    PrefixExpression::PrefixExpression()
        : right(nullptr)
        , op{} { }

    std::string PrefixExpression::toString() const {
        std::stringstream ss;

        ss << "(" << op << right->toString() << ")";

        return ss.str();
    }

}    // namespace arti::monkey
