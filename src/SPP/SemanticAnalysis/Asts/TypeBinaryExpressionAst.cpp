module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.type_binary_expression_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::TypeBinaryExpressionAst::TypeBinaryExpressionAst(
    const std::size_t pos,
    decltype(lhs) &&lhs,
    decltype(op) &&op,
    decltype(rhs) &&rhs):
    Ast{pos},
    lhs{std::move(lhs)},
    op{std::move(op)},
    rhs{std::move(rhs)} {
}

SPP::SemanticAnalysis::Asts::TypeBinaryExpressionAst::~TypeBinaryExpressionAst() = default;

auto SPP::SemanticAnalysis::Asts::TypeBinaryExpressionAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}",
        lhs->print(printer),
        op->print(printer),
        rhs->print(printer));
    return string;
}
