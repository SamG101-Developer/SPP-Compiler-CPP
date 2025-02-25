module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.generic_comp_parameter_required_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::GenericCompParameterRequiredAst::GenericCompParameterRequiredAst(
    const std::size_t pos,
    decltype(tok_cmp) &&tok_cmp,
    decltype(name) &&name,
    decltype(tok_colon) &&tok_colon,
    decltype(type) &&type):
    Ast{pos},
    tok_cmp{std::move(tok_cmp)},
    name{std::move(name)},
    tok_colon{std::move(tok_colon)},
    type{std::move(type)} {
}

SPP::SemanticAnalysis::Asts::GenericCompParameterRequiredAst::~GenericCompParameterRequiredAst() = default;

auto SPP::SemanticAnalysis::Asts::GenericCompParameterRequiredAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}{}",
        tok_cmp->print(printer),
        name->print(printer),
        tok_colon->print(printer),
        type->print(printer));
    return string;
}
