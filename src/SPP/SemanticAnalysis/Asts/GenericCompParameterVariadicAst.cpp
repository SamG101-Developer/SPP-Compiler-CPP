module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.generic_comp_parameter_variadic_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::GenericCompParameterVariadicAst::GenericCompParameterVariadicAst(
    const std::size_t pos,
    decltype(tok_cmp) &&tok_cmp,
    decltype(tok_variadic) &&tok_variadic,
    decltype(name) &&name,
    decltype(tok_colon) &&tok_colon,
    decltype(type) &&type):
    Ast{pos},
    tok_cmp{std::move(tok_cmp)},
    tok_variadic{std::move(tok_variadic)},
    name{std::move(name)},
    tok_colon{std::move(tok_colon)},
    type{std::move(type)} {
}

SPP::SemanticAnalysis::Asts::GenericCompParameterVariadicAst::~GenericCompParameterVariadicAst() = default;

auto SPP::SemanticAnalysis::Asts::GenericCompParameterVariadicAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}{}{}",
        tok_cmp->print(printer),
        tok_variadic->print(printer),
        name->print(printer),
        tok_colon->print(printer),
        type->print(printer));
    return string;
}
