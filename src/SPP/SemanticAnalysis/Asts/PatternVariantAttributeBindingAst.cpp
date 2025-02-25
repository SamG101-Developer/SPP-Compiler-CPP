module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.pattern_variant_attribute_binding_ast;
import spp.semantic_analysis.asts.identifier_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::PatternVariantAttributeBindingAst::PatternVariantAttributeBindingAst(
    const std::size_t pos,
    decltype(name) &&name,
    decltype(tok_assign) &&tok_assign,
    decltype(value) &&value):
    Ast{pos},
    name{std::move(name)},
    tok_assign{std::move(tok_assign)},
    value{std::move(value)} {
}

SPP::SemanticAnalysis::Asts::PatternVariantAttributeBindingAst::~PatternVariantAttributeBindingAst() = default;

auto SPP::SemanticAnalysis::Asts::PatternVariantAttributeBindingAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}",
        name->print(printer),
        tok_assign->print(printer),
        value->print(printer));
    return string;
}
