module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.pattern_variant_expression_ast;


SPP::SemanticAnalysis::Asts::PatternVariantExpressionAst::PatternVariantExpressionAst(
    const std::size_t pos,
    decltype(expr) &&expr):
    Ast{pos},
    expr{std::move(expr)} {
}

SPP::SemanticAnalysis::Asts::PatternVariantExpressionAst::~PatternVariantExpressionAst() = default;

auto SPP::SemanticAnalysis::Asts::PatternVariantExpressionAst::print(Meta::AstPrinter &printer) const -> std::string {
    return expr->print(printer);
}
