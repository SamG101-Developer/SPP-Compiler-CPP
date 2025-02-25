module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.pattern_variant_destructure_skip_1_argument_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::PatternVariantDestructureSkip1ArgumentAst::PatternVariantDestructureSkip1ArgumentAst(
    const std::size_t pos,
    decltype(tok_underscore) &&tok_underscore):
    Ast{pos},
    tok_underscore{std::move(tok_underscore)} {
}

SPP::SemanticAnalysis::Asts::PatternVariantDestructureSkip1ArgumentAst::~PatternVariantDestructureSkip1ArgumentAst() = default;

auto SPP::SemanticAnalysis::Asts::PatternVariantDestructureSkip1ArgumentAst::print(Meta::AstPrinter &printer) const -> std::string {
    return tok_underscore->print(printer);
}
