#include "ast/types/return_statement.hpp"

#include <sstream>

#include <fmt/format.h>

namespace arti::monkey {

    ReturnStatement::ReturnStatement()
        : returnValue(nullptr) { }

    std::string ReturnStatement::toString() const {
        std::stringstream ss;

        ss << tokenLiteral() << " ";

        if (returnValue) {
            ss << returnValue->toString();
        }

        ss << ";";

        return ss.str();
    }

    std::string ReturnStatement::dumpAst(std::string indentation, std::string_view indentStr) const {
        return fmt::format(
            "{}Return\n{}", 
            indentation,
            returnValue->dumpAst(indentation + indentStr.data(), indentStr)
        );
    }

}    // namespace arti::monkey
