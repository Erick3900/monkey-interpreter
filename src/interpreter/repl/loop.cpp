#include "repl/loop.hpp"

#include <sstream>
#include <iostream>

#include <fmt/format.h>

#include "ast/program.hpp"
#include "parser/parser.hpp"
#include "evaluator/impl/tree_walker.hpp"

namespace arti::monkey::repl {

    constexpr std::string_view PROMPT{ "> " };

    int loop() {
        bool astDebug = false;
        std::string line;
        std::stringstream stream;

        Scope scope;

        while (true) {
            std::cout << scope.env.size() << PROMPT << std::flush;

            if (std::getline(std::cin, line)) {
                if (!line.empty() && line[0] == '.') {
                    auto command = std::string_view{ line.begin() + 1, line.end() };

                    if (command == "exit" || command == "quit") {
                        break;
                    }
                    else if (command == "toggleAST") {
                        astDebug = !astDebug;
                    }
                    else if (command == "dumpEnv") {
                        for (const auto &[k, v] : scope.env) {
                            std::cout << k << " " << to_string(*v.get()) << std::endl;
                        }
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
                        auto program = std::move(valid_program).value();

                        auto obj = TreeWalkerEvaluator{}.eval(program.get(), &scope);

                        if (not obj) {
                            std::cout << "Error: " << obj.error() << std::endl;
                        }
                        else {
                            if (obj.value() != nullptr) {
                                std::cout << to_string(*obj.value()) << std::endl;
                            }
                            else {
                                std::cout << "null" << std::endl;
                            }
                        }

                        if (astDebug) {
                            std::cout << program->dumpAst("", " ") << std::endl;
                        }
                    }

                    scope.gcUnnamed();
                }
            }
        }

        return 0;
    }

}
