#include "ast/types/block_statement.hpp"

#include <list>
#include <sstream>

#include <fmt/format.h>

namespace arti::monkey {

    BlockStatement::BlockStatement()
        : statements{} { }

    std::string BlockStatement::toString() const {
        std::stringstream ss;

        for (auto statement : statements) {
            ss << statement->toString();
        }

        return ss.str();
    }

    std::string BlockStatement::dumpAst(std::string indentation, std::string_view indentStr) const {
        std::stringstream ss;

        ss << indentation << "BlockStatement\n";

        std::list<std::string> statementsStr;

        for (auto statement : statements) {
            statementsStr.push_back(statement->dumpAst(indentation + indentStr.data(), indentStr));
        }

        ss << fmt::format("{}", fmt::join(statementsStr, "\n"));

        return ss.str();
    }


}    // namespace arti::monkey
