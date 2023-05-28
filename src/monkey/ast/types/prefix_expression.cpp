#include "ast/types/prefix_expression.hpp"

#include <sstream>

#include <fmt/format.h>

namespace arti::monkey {

    PrefixExpression::PrefixExpression()
        : right(nullptr)
        , op{} { }

    std::string PrefixExpression::toString() const {
        std::stringstream ss;

        ss << "(" << op << right->toString() << ")";

        return ss.str();
    }

    std::string PrefixExpression::dumpAst(std::string indentation, std::string_view indentStr) const {
   std::stringstream ss;

        ss << indentation << "Prefix\n";

        indentation += indentStr.data();

        ss << indentation << "Operator " << op << "\n";

        ss << indentation << "Right\n";
        ss << right->dumpAst(indentation + indentStr.data(), indentStr);

        return ss.str();
    }

}    // namespace arti::monkey
