module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.generic_identifier_ast;
import spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.asts.generic_argument_group_ast;

SPP::SemanticAnalysis::Asts::GenericIdentifierAst::GenericIdentifierAst(
    const std::size_t pos,
    decltype(value) &&value,
    decltype(generic_args_group) &&generic_args_group):
    Ast{pos},
    value{std::move(value)},
    generic_args_group{std::move(generic_args_group)} {
}

SPP::SemanticAnalysis::Asts::GenericIdentifierAst::~GenericIdentifierAst() = default;

auto SPP::SemanticAnalysis::Asts::GenericIdentifierAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        value,
        generic_args_group->print(printer));
    return string;
}
