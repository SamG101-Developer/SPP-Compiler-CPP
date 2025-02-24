module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.binary_expression_ast;
import spp.semantic_analysis.asts.token_ast;

SPP::SemanticAnalysis::Asts::BinaryExpressionAst::BinaryExpressionAst(
    const std::size_t pos,
    decltype(lhs) &&lhs,
    decltype(op) &&op,
    decltype(rhs) &&rhs):
    Ast{pos},
    lhs{std::move(lhs)},
    op{std::move(op)},
    rhs{std::move(rhs)} {
}

SPP::SemanticAnalysis::Asts::BinaryExpressionAst::~BinaryExpressionAst() = default;

auto SPP::SemanticAnalysis::Asts::BinaryExpressionAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{} {} {}",
        lhs->print(printer),
        op->print(printer),
        rhs->print(printer));
    return string;
}
