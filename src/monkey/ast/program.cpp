#include "ast/program.hpp"

#include <sstream>

namespace arti::monkey {

    std::string Program::toString() const {
        std::stringstream ss;

        for (auto node : statements) {
            ss << node->toString();
        }

        return ss.str();
    }

}    // namespace arti::monkey
