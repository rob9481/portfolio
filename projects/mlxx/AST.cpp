#include <format>
#include "AST.h"

namespace AST {

Constant::Constant(TokenType type) {
    tokenType_ = type;
}

auto Constant::toString() const -> std::string {
    return std::format("Constant({})", ::toString(tokenType_));
}

auto Constant::visit(Visitor &visitor) const -> void {
    visitor.accept(*this);
}

ValueName::ValueName(Token token) : token_(token) {}

auto ValueName::toString() const -> std::string {
    return std::format("ValueName({})", token_.toString());
}

auto ValueName::visit(Visitor &visitor) const -> void {
    visitor.accept(*this);
}

LetBinding::LetBinding(ValueName *valueName, Expr *expr) {
    valueName_ = valueName;
    expr_ = expr;
}

auto LetBinding::toString() const -> std::string {
    return std::format("LetBinding({}, {})", valueName_->toString(), expr_->toString());
}

auto LetBinding::visit(Visitor &visitor) const -> void {
    visitor.accept(*this);
}

ExprConstant::ExprConstant(Constant *constant) {
    constant_ = constant;
}

auto ExprConstant::toString() const -> std::string {
    return std::format("ExprConstant({})", constant_->toString());
}

auto ExprConstant::visit(Visitor &visitor) const -> void {
    visitor.accept(*this);
}

ExprLet::ExprLet(bool rec, LetBinding *letBinding, Expr *expr) {
    rec_ = rec;
    letBinding_ = letBinding;
    expr_ = expr;
}

auto ExprLet::toString() const -> std::string {
    return std::format("ExprLet({}, {}, {})",
                        rec_,
                        letBinding_->toString(),
                        expr_->toString());
}

auto ExprLet::visit(Visitor &visitor) const -> void {
    visitor.accept(*this);
}

} // AST

