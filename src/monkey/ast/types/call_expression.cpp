#include "ast/types/call_expression.hpp"

#include <list>
#include <sstream>
#include <algorithm>

#include <fmt/format.h>

namespace arti::monkey {

    CallExpression::CallExpression()
        : function(nullptr)
        , arguments{} { }

    std::string CallExpression::toString() const {
        std::stringstream ss;

        std::list<std::string> argsStrs;

        std::ranges::for_each(
            arguments, 
            [&](ASTNode *a) {
                argsStrs.emplace_back(a->toString());
            }
        );

        ss << function->toString();

        ss << fmt::format(
            "({})", 
            fmt::join(argsStrs, ", ")
        );

        return ss.str();
    }

}    // namespace arti::monkey
