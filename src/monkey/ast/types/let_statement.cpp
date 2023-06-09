#include "ast/types/let_statement.hpp"

#include <sstream>

#include <fmt/format.h>

namespace arti::monkey {

    LetStatement::LetStatement()
        : name(nullptr)
        , value(nullptr) { }

    std::string LetStatement::toString() const {
        std::stringstream ss;

        ss << tokenLiteral() << " " << name->toString() << " = ";

        if (value) {
            ss << value->toString();
        }

        ss << ";";

        return ss.str();
    }

    std::string LetStatement::dumpAst(std::string indentation, std::string_view indentStr) const {
        return fmt::format(
            "{}Let\n{}\n{}", 
            indentation,
            fmt::format(
                "{}Name\n{}",
                indentation + indentStr.data(),
                name->dumpAst(indentation + indentStr.data() + indentStr.data(), indentStr)
            ),
            fmt::format(
                "{}Value\n{}",
                indentation + indentStr.data(),
                value->dumpAst(indentation + indentStr.data() + indentStr.data(), indentStr)
            )
        );
    }

}    // namespace arti::monkey
