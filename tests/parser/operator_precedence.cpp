#include <gtest/gtest.h>

#include <array>
#include <ranges>
#include <sstream>
#include <algorithm>
#include <cassert>

#include "lexer/lexer.hpp"
#include "ast/ast.hpp"
#include "parser/parser.hpp"

constexpr auto expectedOutput = 
R"(((-a) * b)
(!(-a))
((a + b) + c)
((a + b) - c)
((a * b) * c)
((a * b) / c)
(a + (b / c))
(((a + (b * c)) + (d / e)) - f)
(3 + 4)((-5) * 5)
((5 > 4) == (3 < 4))
((5 < 4) != (3 > 4))
((3 + (4 * 5)) == ((3 * 1) + (4 * 5)))
)";

TEST(parser, operator_precedence) {
    using namespace arti::monkey;

    std::ifstream input{ "../tests/parser/operator_precedence.mnky" };
    std::stringstream expectedStream{ expectedOutput };

    std::string line;
    std::string expectedLine;


    while (std::getline(input, line)) {
        std::getline(expectedStream, expectedLine);

        auto parser = [&]{
            auto lexer = std::make_unique<Lexer>(std::make_unique<std::stringstream>(line));

            return std::make_unique<Parser>(std::move(lexer));
        }();

        auto program_ex = parser->parseProgram();

        if (not program_ex) {
            throw std::runtime_error(program_ex.error());
        }

        auto program = std::move(program_ex).value();

        EXPECT_EQ(program->toString(), expectedLine);
    }
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
