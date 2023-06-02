#pragma once

#include <list>
#include <memory>
#include <unordered_map>

#include "object/object.hpp"

namespace arti::monkey {

    struct Scope {
        size_t unnamedCount = 0;
        std::list<std::string_view> unnamed;
        std::unordered_map<std::string_view, std::unique_ptr<Object>> env;

        void gcUnnamed();
        Object *newUnamed();
        Object *newObject(std::string name);
        Object *get(std::string_view name) const;
        Object *set(std::string_view name, std::unique_ptr<Object> object);
        std::unique_ptr<Object> takeOwnership(std::string_view name);
    };

}
