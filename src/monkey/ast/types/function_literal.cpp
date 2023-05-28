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

    std::string FunctionLiteral::dumpAst(std::string indentation, std::string_view indentStr) const {
        std::stringstream ss;

        ss << indentation << "FunctionLiteral\n";

        indentation += indentStr.data();

        ss << indentation << "Parameters\n";

        std::list<std::string> parametersStrs;

        std::ranges::for_each(
            parameters, 
            [&](Identifier *p) {
                parametersStrs.emplace_back(p->dumpAst(indentation + indentStr.data(), indentStr));
            }
        );

        ss << fmt::format(
            "{}", 
            fmt::join(parametersStrs, "\n")
        );

        ss << "\n";

        ss << indentation << "Body\n";
        ss << statement->dumpAst(indentation + indentStr.data(), indentStr);

        return ss.str();
    }

}    // namespace arti::monkey
