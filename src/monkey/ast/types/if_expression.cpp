#include "ast/types/if_expression.hpp"

#include <sstream>

#include <fmt/format.h>

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

    std::string IfExpression::dumpAst(std::string indentation, std::string_view indentStr) const {
        auto ss = fmt::format(
            "{}If\n{}\n{}", 
            indentation, 
            condition->dumpAst(indentation + indentStr.data(), indentStr),
            consequence->dumpAst(indentation + indentStr.data(), indentStr)
        );

        if (alternative != nullptr) {
            return ss + fmt::format(
                "\n{}Else\n{}",
                indentation,
                consequence->dumpAst(indentation + indentStr.data(), indentStr)
            );
        }

        return ss;
    }

}    // namespace arti::monkey
