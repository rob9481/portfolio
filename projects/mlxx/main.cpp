#include <iostream>
#include "AST.h"
#include "Parser.h"

class PrettyPrinter : public AST::Visitor {
public:
    auto getOutput() const -> std::string { return output_; }

private:
    std::string output_;

private:
    auto accept(const AST::Constant &constant) -> void override {
        std::string str;
        switch(constant.getType()) {
        using enum TokenType;
        case And:
            str = "and";
            break;
        case False:
            str = "false";
            break;
        case In:
            str = "in";
            break;
        case Let:
            str = "let";
            break;
        case Rec:
            str = "rec";
            break;
        case True:
            str = "true";
            break;
        case Equal:
            str = "=";
            break;
        case Unit:
            str = "()";
            break;
        default:
            break;
        }
        output_ += str;
    }

    auto accept(const AST::ValueName &valueName) -> void override {
        output_ += valueName.getToken().getLexeme();
    }

    auto accept(const AST::LetBinding &letBinding) -> void override {
        letBinding.getValueName()->visit(*this);
        output_ += " = ";
        letBinding.getExpr()->visit(*this);
    }

    auto accept(const AST::ExprConstant &exprConstant) -> void override {
        exprConstant.getConstant()->visit(*this);
    }

    auto accept(const AST::ExprLet &exprLet) -> void override {
        output_ += "let ";
        if (exprLet.getRec())
            output_ += "rec ";
        exprLet.getLetBinding()->visit(*this);
        output_ += " in ";
        exprLet.getExpr()->visit(*this);
    }
};

int main() {
    const std::string input = "let rec f = false in ()";
    try {
        Lexer lexer(input);
        std::cout << "INPUT:      " << input << '\n';

        const auto *ast = Parser(&lexer).parse();
        std::cout << "AST OUTPUT: " << ast->toString() << '\n';

        PrettyPrinter pp;
        ast->visit(pp);
        std::cout << "PP OUTPUT:  " << pp.getOutput() << '\n';
    }
    catch (std::runtime_error const& error) {
        std::cout << "runtime_error: " << error.what() << std::endl;
    }

    return 0;
}
