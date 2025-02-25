module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.generic_type_parameter_inline_constraints_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::GenericTypeParameterInlineConstraintsAst::GenericTypeParameterInlineConstraintsAst(
    const std::size_t pos,
    decltype(tok_colon) &&tok_colon,
    decltype(type) &&type):
    Ast{pos},
    tok_colon{std::move(tok_colon)},
    type{std::move(type)} {
}

SPP::SemanticAnalysis::Asts::GenericTypeParameterInlineConstraintsAst::~GenericTypeParameterInlineConstraintsAst() = default;

auto SPP::SemanticAnalysis::Asts::GenericTypeParameterInlineConstraintsAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        tok_colon->print(printer),
        type->print(printer));
    return string;
}
