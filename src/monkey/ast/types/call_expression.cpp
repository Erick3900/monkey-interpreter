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

    std::string CallExpression::dumpAst(std::string indentation, std::string_view indentStr) const {
        std::stringstream ss;

        ss << indentation << "CallExpression\n";

        indentation += indentStr.data();

        ss << indentation << "Function\n" << function->dumpAst(indentation + indentStr.data(), indentStr) << "\n";

        ss << indentation << "Arguments\n";

        std::list<std::string> argsStrs;

        std::ranges::for_each(
            arguments, 
            [&](ASTNode *a) {
                argsStrs.emplace_back(a->dumpAst(indentation + indentStr.data(), indentStr));
            }
        );

        ss << fmt::format(
            "{}", 
            fmt::join(argsStrs, "\n")
        );

        return ss.str();
    }

}    // namespace arti::monkey
