#pragma once

#include <string>
#include <memory>
#include <cstdint>
#include <variant>
#include <unordered_map>

namespace arti::monkey {

    struct Scope;

    struct Null_t { };

    struct Object {
        using Value_t = std::variant<
            Null_t,
            bool,
            int64_t,
            std::string
        >;

        bool isReturn;
        Scope *owner;

        std::string name;
        Value_t value;

        bool isUnnamed() const;
        std::unique_ptr<Object> takeOwnership() const;

        Object();
        ~Object() = default;

        Object(Object &&) = default;
        Object(const Object &) = default;

        Object &operator=(Object &&) = default;
        Object &operator=(const Object &) = default;
    };

    std::string to_string(const arti::monkey::Object &obj);

}
