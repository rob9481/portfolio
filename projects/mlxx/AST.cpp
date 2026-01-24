#include "AST.h"
#include <format>

namespace AST {

Constant::Constant(TokenType type) { tokenType_ = type; }

auto Constant::toString() const -> std::string {
  return std::format("Constant({})", ::toString(tokenType_));
}

auto Constant::visit(Visitor &visitor) const -> void { visitor.accept(*this); }

ValueName::ValueName(Token token) : token_(token) {}

auto ValueName::toString() const -> std::string {
  return std::format("ValueName({})", token_.toString());
}

auto ValueName::visit(Visitor &visitor) const -> void { visitor.accept(*this); }

LetBinding::LetBinding(std::unique_ptr<ValueName> &&valueName,
                       std::unique_ptr<Expr> &&expr) {
  valueName_ = std::move(valueName);
  expr_ = std::move(expr);
}

auto LetBinding::toString() const -> std::string {
  return std::format("LetBinding({}, {})", valueName_->toString(),
                     expr_->toString());
}

auto LetBinding::visit(Visitor &visitor) const -> void {
  visitor.accept(*this);
}

ExprConstant::ExprConstant(std::unique_ptr<Constant> &&constant) {
  constant_ = std::move(constant);
}

auto ExprConstant::toString() const -> std::string {
  return std::format("ExprConstant({})", constant_->toString());
}

auto ExprConstant::visit(Visitor &visitor) const -> void {
  visitor.accept(*this);
}

ExprLet::ExprLet(bool rec, std::unique_ptr<LetBinding> &&letBinding,
                 std::unique_ptr<Expr> &&expr) {
  rec_ = rec;
  letBinding_ = std::move(letBinding);
  expr_ = std::move(expr);
}

auto ExprLet::toString() const -> std::string {
  return std::format("ExprLet({}, {}, {})", rec_, letBinding_->toString(),
                     expr_->toString());
}

auto ExprLet::visit(Visitor &visitor) const -> void { visitor.accept(*this); }

} // namespace AST
