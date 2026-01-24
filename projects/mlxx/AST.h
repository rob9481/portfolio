#ifndef AST_H
#define AST_H

#include <memory>
#include <string>
#include "Token.h"

namespace AST {

class Visitor;

class Root {
public:
    virtual ~Root() {}
    virtual auto toString() const -> std::string = 0;
    virtual auto visit(Visitor &visitor) const -> void = 0;
};

class Constant : public Root {
public:
    explicit Constant(TokenType type);
    auto toString() const -> std::string override;
    auto visit(Visitor &visitor) const -> void override;

    auto getType() const -> TokenType { return tokenType_; }

private:
    TokenType tokenType_;
};

class ValueName : public Root {
public:
    explicit ValueName(Token token);
    auto toString() const -> std::string override;
    auto visit(Visitor &visitor) const -> void override;

    auto getToken() const -> Token { return token_; }

private:
    Token token_;
};

class Expr : public Root {};

class LetBinding : public Root {
public:
    LetBinding(std::unique_ptr<ValueName>&& valueName, std::unique_ptr<Expr>&& expr);
    auto toString() const -> std::string override;
    auto visit(Visitor &visitor) const -> void override;

    auto getValueName() const -> ValueName const * { return valueName_.get(); }
    auto getExpr() const -> Expr const * { return expr_.get(); }

private:
    std::unique_ptr<ValueName> valueName_;
    std::unique_ptr<Expr> expr_;
};

class ExprConstant : public Expr {
public:
    ExprConstant(std::unique_ptr<Constant>&& constant);
    auto toString() const -> std::string override;
    auto visit(Visitor &visitor) const -> void override;

    auto getConstant() const -> Constant const * { return constant_.get(); }

private:
    std::unique_ptr<Constant> constant_;
};

class ExprLet : public Expr {
public:
    ExprLet(bool rec, std::unique_ptr<LetBinding>&& letBinding, std::unique_ptr<Expr>&& expr);
    auto toString() const -> std::string override;
    auto visit(Visitor &visitor) const -> void override;

    auto getRec() const -> bool { return rec_; }
    auto getLetBinding() const -> LetBinding const * { return letBinding_.get(); }
    auto getExpr() const -> Expr const * { return expr_.get(); }

private:
    bool rec_;
    std::unique_ptr<LetBinding> letBinding_;
    std::unique_ptr<Expr> expr_;
};

class Visitor {
public:
    virtual auto accept(const Constant &) -> void = 0;
    virtual auto accept(const ValueName &) -> void = 0;
    virtual auto accept(const LetBinding &) -> void = 0;
    virtual auto accept(const ExprConstant &) -> void = 0;
    virtual auto accept(const ExprLet &) -> void = 0;
};

} // AST

#endif // AST_H
