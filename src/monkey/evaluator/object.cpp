#include "object/object.hpp"

#include <fmt/format.h>

#include "utils/overload_set.hpp"
#include "evaluator/scope.hpp"

namespace arti::monkey {
    constexpr std::string_view unnamed_prefix{ "__unnamed_" };

    Object::Object()
        : isReturn(false)
        , owner(nullptr)
        , name{}
        , value{} {}

    bool Object::isUnnamed() const {
        if (name.length() > 12) {
            return std::string_view{ name.begin(), name.begin() + unnamed_prefix.size() } == unnamed_prefix;
        }

        return false;
    }

    std::unique_ptr<Object> Object::takeOwnership() const {
        return owner->takeOwnership(name);
    }

    std::string to_string(const arti::monkey::Object &obj) {
        using namespace arti::monkey;

        return std::visit(
            nstd::OverloadSet{
                [&](Null_t) -> std::string {
                    return "null";
                },
                [&](bool value) -> std::string {
                    return (value ? "true" : "false");
                },
                [&](int64_t value) -> std::string{
                    return fmt::to_string(value);
                },
                [&](const std::string &value) -> std::string {
                    return fmt::format("\"{}\"", value);
                },
            },
            obj.value
        );
    }

}
