#pragma once

#include <tl/expected.hpp>

#include "ast/program.hpp"
#include "object/object.hpp"
#include "evaluator/scope.hpp"

namespace arti::monkey {

    struct Evaluator {
        virtual tl::expected<Object *, std::string> eval(Program *program, Scope *scope) = 0;
        virtual tl::expected<std::pair<Object *, std::unique_ptr<Scope>>, std::string> eval(Program *program) = 0;
    };

}
