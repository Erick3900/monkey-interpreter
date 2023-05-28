#include <iostream>
#include <filesystem>

#include <internal/config.hpp>

#include <fmt/format.h>
#include <docopt/docopt.h>

#include "repl/loop.hpp"
#include "parser/parser.hpp"

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
            auto parser = arti::monkey::Parser{ std::make_unique<arti::monkey::Lexer>(std::make_unique<std::ifstream>(file)) };

            auto valid_program = parser.parseProgram();

            if (not valid_program) {
                std::cout << "Error: " << valid_program.error() << std::endl;
            }
            else {
                std::cout << valid_program.value()->dumpAst("", "  ") << std::endl;
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
