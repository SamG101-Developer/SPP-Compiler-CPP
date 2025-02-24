module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.unary_expression_ast;


SPP::SemanticAnalysis::Asts::UnaryExpressionAst::UnaryExpressionAst(
    const std::size_t pos,
    decltype(op) &&op,
    decltype(rhs) &&rhs):
    Ast{pos},
    op{std::move(op)},
    rhs{std::move(rhs)} {
}

SPP::SemanticAnalysis::Asts::UnaryExpressionAst::~UnaryExpressionAst() = default;

auto SPP::SemanticAnalysis::Asts::UnaryExpressionAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        op->print(printer),
        rhs->print(printer));
    return string;
}
