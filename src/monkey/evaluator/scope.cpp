#include "evaluator/scope.hpp"

#include <fmt/format.h>

namespace arti::monkey {

    Object *Scope::get(std::string_view name) const {
        if (auto it = env.find(name); it != env.end()) {
            return it->second.get();
        }

        return nullptr;
    }

    Object *Scope::set(std::string_view name, std::unique_ptr<Object> object) {
        env[name] = std::move(object);
        return env[name].get();
    }

    Object *Scope::newUnamed() {
        auto obj = std::make_unique<Object>();

        obj->name = fmt::format("__unnamed_{}__", unnamedCount++);
        obj->owner = this;

        std::string_view name = obj->name;

        env[name] = std::move(obj);

        unnamed.push_back(name);

        return env[name].get();
    }

    Object *Scope::newObject(std::string name) {
        auto obj = std::make_unique<Object>();

        obj->name = std::move(name);
        obj->owner = this;

        std::string_view Name = obj->name;

        env[Name] = std::move(obj);

        return env[Name].get();
    }

    std::unique_ptr<Object> Scope::takeOwnership(std::string_view name) {
        if (env.contains(name)) {
            std::unique_ptr<Object> ret;
            env.at(name).swap(ret);
            env.erase(name);
            return ret;
        }
        return nullptr;
    }

    void Scope::gcUnnamed() {
        for (auto u : unnamed) {
            env.erase(u);
        }
        unnamed.clear();
    }

}
