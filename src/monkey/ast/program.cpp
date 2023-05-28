#include "ast/program.hpp"

#include <stack>
#include <sstream>

namespace arti::monkey {

    std::string Program::toString() const {
        std::stringstream ss;

        for (auto node : statements) {
            ss << node->toString();
        }

        return ss.str();
    }

    std::string Program::dumpAst(std::string indentation, std::string_view indentStr) const {
        std::stringstream dump;

        dump << indentation << "Program\n";

        for (auto statement : statements) {
            dump << statement->dumpAst(indentation + indentStr.data(), indentStr) << '\n';
        }

        return dump.str();
    }

}    // namespace arti::monkey
