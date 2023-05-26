#include "repl/loop.hpp"

#include <sstream>
#include <iostream>

#include <fmt/format.h>

#include "parser/parser.hpp"

namespace arti::monkey::repl {

    constexpr std::string_view PROMPT{ "> " };

    int loop() {
        std::string line;
        std::stringstream stream;

        while (true) {
            std::cout << PROMPT << std::flush;

            if (std::getline(std::cin, line)) {
                if (!line.empty() && line[0] == '.') {
                    auto command = std::string_view{ line.begin() + 1, line.end() };

                    if (command == "exit") {
                        break;
                    }
                    else {
                        std::cout << fmt::format("Error, invalid command '{}'", command) << std::endl;
                    }
                }
                else {
                    auto parser = Parser{ std::make_unique<Lexer>(std::make_unique<std::stringstream>(line)) };

                    auto valid_program = parser.parseProgram();

                    if (not valid_program) {
                        std::cout << "Error: " << valid_program.error() << std::endl;
                    }
                    else {
                        std::cout << valid_program.value()->toString() << std::endl;
                    }
                }
            }
        }

        return 0;
    }

}
