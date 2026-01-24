#include <iostream>
#include "AST.h"
#include "Parser.h"

int main() {
    const std::string input = "let rec f = false in ()";
    try {
        Lexer lexer(input);
        std::cout << "INPUT:      " << input << '\n';

        const auto *ast = Parser(&lexer).parse();
        std::cout << "AST OUTPUT: " << ast->toString() << '\n';
    }
    catch (std::runtime_error const& error) {
        std::cout << "runtime_error: " << error.what() << std::endl;
    }

    return 0;
}
