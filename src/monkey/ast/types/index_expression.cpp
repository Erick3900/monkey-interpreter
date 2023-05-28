#include "ast/types/index_expression.hpp"

#include <sstream>

#include <fmt/format.h>

namespace arti::monkey {

    IndexExpression::IndexExpression()
        : left(nullptr)
        , index(nullptr) {}

    std::string IndexExpression::toString() const {
        return fmt::format("{}[{}]", left->toString(), index->toString());
    }

    std::string IndexExpression::dumpAst(std::string indentation, std::string_view indentStr) const {
        std::stringstream ss;

        ss << indentation << "IndexExpression\n";
        indentation += indentStr.data();
        ss << indentation << "Left\n";
        ss << left->dumpAst(indentation + indentStr.data(), indentStr);
        ss << '\n' << indentation << "Index\n";
        ss << index->dumpAst(indentation + indentStr.data(), indentStr);

        return ss.str();
    }

}
