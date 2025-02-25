module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.pattern_variant_else_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::PatternVariantElseAst::PatternVariantElseAst(
    const std::size_t pos,
    decltype(tok_else) &&tok_else):
    Ast{pos},
    tok_else{std::move(tok_else)} {
}

SPP::SemanticAnalysis::Asts::PatternVariantElseAst::~PatternVariantElseAst() = default;

auto SPP::SemanticAnalysis::Asts::PatternVariantElseAst::print(Meta::AstPrinter &printer) const -> std::string {
    return tok_else->print(printer);
}
