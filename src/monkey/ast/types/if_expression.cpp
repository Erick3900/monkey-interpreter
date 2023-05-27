#include "ast/types/if_expression.hpp"

#include <sstream>

namespace arti::monkey {

    IfExpression::IfExpression()
        : condition(nullptr)
        , consequence(nullptr)
        , alternative(nullptr) { }

    std::string IfExpression::toString() const {
        std::stringstream ss;

        ss << "if " << condition->toString() << " " << consequence->toString();

        if (alternative != nullptr) {
            ss << "else " << alternative->toString();
        }

        return ss.str();
    }

}    // namespace arti::monkey
