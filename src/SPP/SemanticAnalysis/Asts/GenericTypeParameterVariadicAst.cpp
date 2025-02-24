module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.generic_type_parameter_variadic_ast;
import spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.asts.generic_type_parameter_inline_constraints_ast;


SPP::SemanticAnalysis::Asts::GenericTypeParameterVariadicAst::GenericTypeParameterVariadicAst(
    const std::size_t pos,
    decltype(tok_variadic) &&tok_variadic,
    decltype(name) &&name,
    decltype(constraints) &&constraints):
    Ast{pos},
    tok_variadic{std::move(tok_variadic)},
    name{std::move(name)},
    constraints{std::move(constraints)} {
}

SPP::SemanticAnalysis::Asts::GenericTypeParameterVariadicAst::~GenericTypeParameterVariadicAst() = default;

auto SPP::SemanticAnalysis::Asts::GenericTypeParameterVariadicAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}",
        tok_variadic->print(printer),
        name->print(printer),
        constraints.has_value() ? constraints.value()->print(printer) : "");
    return string;
}
