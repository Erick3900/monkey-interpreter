#include "ast/types/hash_literal.hpp"

#include <list>
#include <sstream>
#include <algorithm>

#include <fmt/format.h>

#include "ast/types/string_literal.hpp"

namespace arti::monkey {

    HashLiteral::HashLiteral()
        : elements{} { }

    std::string HashLiteral::toString() const {
        std::stringstream ss;

        std::list<std::string> parametersStrs;

        std::ranges::for_each(
            elements, 
            [&](const std::pair<ASTNode *, ASTNode *> &el) {
                if (dynamic_cast<StringLiteral*>(el.first) != nullptr) {
                    parametersStrs.push_back(fmt::format("[{}]: {}", el.first->toString(), el.second->toString()));
                }
                else {
                    parametersStrs.push_back(fmt::format("{}: {}", el.first->toString(), el.second->toString()));
                }
            }
        );

        ss << "{";

        ss << fmt::format(
            "{}", 
            fmt::join(parametersStrs, ",\n")
        );

        ss << "]";

        return ss.str();
    }

    std::string HashLiteral::dumpAst(std::string indentation, std::string_view indentStr) const {
        std::stringstream ss;

        ss << indentation << "HashLiteral\n";

        indentation += indentStr.data();

        ss << indentation << "Elements\n";

        std::list<std::string> parametersStrs;

        indentation += indentStr.data();
        std::ranges::for_each(
            elements, 
            [&](const std::pair<ASTNode *, ASTNode *> &el) {
                parametersStrs.push_back(fmt::format(
                    "{}Element\n{}Key\n{}\n{}Value\n{}",
                    indentation,
                    indentation + indentStr.data(),
                    el.first->dumpAst(indentation + indentStr.data() + indentStr.data(), indentStr), 
                    indentation + indentStr.data(),
                    el.second->dumpAst(indentation + indentStr.data() + indentStr.data(), indentStr)
                ));
            }
        );

        ss << fmt::format("{}", fmt::join(parametersStrs, "\n"));

        return ss.str();
    }

}    // namespace arti::monkey
