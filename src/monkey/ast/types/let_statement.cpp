#include "ast/types/let_statement.hpp"

#include <sstream>

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

}    // namespace arti::monkey
