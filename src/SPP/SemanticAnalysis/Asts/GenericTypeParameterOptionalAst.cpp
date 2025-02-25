module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.generic_type_parameter_optional_ast;
import spp.semantic_analysis.asts.generic_type_parameter_inline_constraints_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::GenericTypeParameterOptionalAst::GenericTypeParameterOptionalAst(
    const std::size_t pos,
    decltype(name) &&name,
    decltype(constraints) &&constraints,
    decltype(tok_assign) &&tok_assign,
    decltype(default_type) &&default_type):
    Ast{pos},
    name{std::move(name)},
    constraints{std::move(constraints)},
    tok_assign{std::move(tok_assign)},
    default_type{std::move(default_type)} {
}

SPP::SemanticAnalysis::Asts::GenericTypeParameterOptionalAst::~GenericTypeParameterOptionalAst() = default;

auto SPP::SemanticAnalysis::Asts::GenericTypeParameterOptionalAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{} {} {}",
        name->print(printer),
        constraints.has_value() ? constraints.value()->print(printer) : "",
        tok_assign->print(printer),
        default_type->print(printer));
    return string;
}
