module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.pattern_variant_literal_ast;


SPP::SemanticAnalysis::Asts::PatternVariantLiteralAst::PatternVariantLiteralAst(
    const std::size_t pos,
    decltype(literal) &&literal):
    Ast{pos},
    literal{std::move(literal)} {
}

SPP::SemanticAnalysis::Asts::PatternVariantLiteralAst::~PatternVariantLiteralAst() = default;

auto SPP::SemanticAnalysis::Asts::PatternVariantLiteralAst::print(Meta::AstPrinter &printer) const -> std::string {
    return literal->print(printer);
}
