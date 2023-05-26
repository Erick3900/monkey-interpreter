#include "repl/loop.hpp"

#include <sstream>
#include <iostream>

#include <fmt/format.h>

#include "lexer/lexer.hpp"

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
                    auto lexer = Lexer{ std::make_unique<std::stringstream>( line ) };

                    for (const auto &token : lexer.tokensIterator()) {
                        std::cout << token << std::endl;
                    }
                }
            }
        }

        return 0;
    }

}
