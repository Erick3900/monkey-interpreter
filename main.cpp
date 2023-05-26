#include <iostream>
#include <filesystem>

#include <internal/config.hpp>

#include <fmt/format.h>
#include <docopt/docopt.h>

#include "repl/loop.hpp"
#include "lexer/lexer.hpp"

const auto Usage{
    fmt::format(
        R"(Monkey.
    {}

    Usage:
        monkey
        monkey <file>

    Options:
        --help      Show this screen
        --version   Show program version
    )",
        arti::config::project_description
    )
};

int main(int argc, char* argv[]) {
    using OptionsMap_t = std::map<std::string, docopt::value>;

    const OptionsMap_t options = docopt::docopt(
        Usage,
        { argv + 1, argv + argc },
        true,
        fmt::format("{} v{}, by {}",
            arti::config::project_name,
            arti::config::project_version,
            arti::config::project_author_github
        )
    );

    if (options.at("<file>").kind() != docopt::Kind::Empty) {
        auto file = options.at("<file>").asString();

        if (std::filesystem::exists(file)) {
            auto lexer = arti::monkey::Lexer{ file };

            for (const auto &token : lexer) {
                std::cout << token << std::endl;
            }
        }
        else {
            fmt::print("Error: File '{}', does not exist\n", file);
        }
    }
    else {
        std::cout << fmt::format("Wrlcome to the monkey lang repl!") << std::endl;

        return arti::monkey::repl::loop();
    }
}
