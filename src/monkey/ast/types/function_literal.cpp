#include "ast/types/function_literal.hpp"

#include <list>
#include <sstream>
#include <algorithm>

#include <fmt/format.h>

namespace arti::monkey {

    FunctionLiteral::FunctionLiteral()
        : parameters{}
        , statement(nullptr) { }

    std::string FunctionLiteral::toString() const {
        std::stringstream ss;

        std::list<std::string> parametersStrs;

        std::ranges::for_each(
            parameters, 
            [&](Identifier *p) {
                parametersStrs.emplace_back(p->toString());
            }
        );

        ss << tokenLiteral();

        ss << fmt::format(
            "({})", 
            fmt::join(parametersStrs, ", ")
        );

        ss << statement->toString();

        return ss.str();
    }

}    // namespace arti::monkey
