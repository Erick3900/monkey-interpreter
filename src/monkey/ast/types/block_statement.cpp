#include "ast/types/block_statement.hpp"

#include <sstream>

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

}    // namespace arti::monkey
