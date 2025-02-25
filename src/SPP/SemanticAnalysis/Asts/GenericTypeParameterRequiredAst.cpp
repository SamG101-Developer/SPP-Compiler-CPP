module;
#include <format>
#include <ranges>

module spp.semantic_analysis.asts.generic_type_parameter_required_ast;
import spp.semantic_analysis.asts.generic_type_parameter_inline_constraints_ast;


SPP::SemanticAnalysis::Asts::GenericTypeParameterRequiredAst::GenericTypeParameterRequiredAst(
    const std::size_t pos,
    decltype(name) &&name,
    decltype(constraints) &&constraints):
    Ast{pos},
    name{std::move(name)},
    constraints{std::move(constraints)} {
}

SPP::SemanticAnalysis::Asts::GenericTypeParameterRequiredAst::~GenericTypeParameterRequiredAst() = default;

auto SPP::SemanticAnalysis::Asts::GenericTypeParameterRequiredAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        name->print(printer),
        constraints.has_value() ? constraints.value()->print(printer) : "");
    return string;
}
