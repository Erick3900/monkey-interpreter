#include "ast/types/return_statement.hpp"

#include <sstream>

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

}    // namespace arti::monkey
