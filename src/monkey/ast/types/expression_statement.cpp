#include "ast/types/expression_statement.hpp"

#include <string>

#include <fmt/format.h>

namespace arti::monkey {

    ExpressionStatement::ExpressionStatement()
        : expression(nullptr) { }

    std::string ExpressionStatement::toString() const {
        if (expression) {
            return expression->toString();
        }

        return "";
    }

    std::string ExpressionStatement::dumpAst(std::string indentation, std::string_view indentStr) const {
        return fmt::format(
            "{}Expression\n{}", 
            indentation, 
            expression->dumpAst(indentation + indentStr.data(), indentStr)
        );
    }

}    // namespace arti::monkey
