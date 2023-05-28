#include "ast/types/array_literal.hpp"

#include <list>
#include <sstream>

#include <fmt/format.h>

namespace arti::monkey {

    ArrayLiteral::ArrayLiteral()
        : elements{} { }

    std::string ArrayLiteral::toString() const {
        std::stringstream ss;

        std::list<std::string> elementsStr;

        for (auto el : elements) {
            elementsStr.push_back(el->toString());
        }

        ss << fmt::format("[{}", fmt::join(elementsStr, ", "));

        return ss.str();
    }

    std::string ArrayLiteral::dumpAst(std::string indentation, std::string_view indentStr) const {
        std::stringstream ss;

        ss << indentation << "ArrayLiteral\n";

        std::list<std::string> elementsStr;

        for (auto el : elements) {
            elementsStr.push_back(el->dumpAst(indentation + indentStr.data(), indentStr));
        }

        ss << fmt::format("{}", fmt::join(elementsStr, "\n"));

        return ss.str();
    }

}    // namespace arti::monkey
