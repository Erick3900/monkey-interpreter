#include "ast/types/infix_expression.hpp"

#include <sstream>

#include <fmt/format.h>

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

    std::string InfixExpression::dumpAst(std::string indentation, std::string_view indentStr) const {
        std::stringstream ss;

        ss << indentation << "Infix\n";

        indentation += indentStr.data();

        ss << indentation << "Operator " << op << "\n";

        ss << indentation << "Left\n";
        ss << left->dumpAst(indentation + indentStr.data(), indentStr);
        ss << "\n";

        ss << indentation << "Right\n";
        ss << right->dumpAst(indentation + indentStr.data(), indentStr);

        return ss.str();
    }

}    // namespace arti::monkey
