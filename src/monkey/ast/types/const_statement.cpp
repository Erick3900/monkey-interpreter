#include "ast/types/const_statement.hpp"

#include <sstream>

#include <fmt/format.h>

namespace arti::monkey {

    ConstStatement::ConstStatement()
        : name(nullptr)
        , value(nullptr) { }

    std::string ConstStatement::toString() const {
        std::stringstream ss;

        ss << tokenLiteral() << " " << name->toString() << " = ";

        if (value) {
            ss << value->toString();
        }

        ss << ";";

        return ss.str();
    }

    std::string ConstStatement::dumpAst(std::string indentation, std::string_view indentStr) const {
        return fmt::format(
            "{}Const\n{}\n{}", 
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
