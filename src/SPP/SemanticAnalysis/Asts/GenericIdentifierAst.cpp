module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.generic_identifier_ast;
import spp.semantic_analysis.asts.generic_argument_group_ast;
import spp.semantic_analysis.asts.identifier_ast;
import spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.asts.type_single_ast;

SPP::SemanticAnalysis::Asts::GenericIdentifierAst::GenericIdentifierAst(
    const std::size_t pos,
    decltype(value) &&value,
    decltype(generic_args_group) &&generic_args_group):
    Ast{pos},
    value{std::move(value)},
    generic_args_group{std::move(generic_args_group)} {
}

auto SPP::SemanticAnalysis::Asts::GenericIdentifierAst::from(IdentifierAst const &identifier) -> std::unique_ptr<GenericIdentifierAst> {
    return std::make_unique<GenericIdentifierAst>(identifier.pos, identifier.value.c_str(), GenericArgumentGroupAst::from_empty());
}

auto SPP::SemanticAnalysis::Asts::GenericIdentifierAst::from(TypeSingleAst const &identifier) -> std::unique_ptr<GenericIdentifierAst> {
    return std::make_unique<GenericIdentifierAst>(identifier.pos, identifier.name->value.c_str(), GenericArgumentGroupAst::from_empty());
}

auto SPP::SemanticAnalysis::Asts::GenericIdentifierAst::from(GenericIdentifierAst const &identifier) -> std::unique_ptr<GenericIdentifierAst> {
    return std::make_unique<GenericIdentifierAst>(identifier.pos, identifier.value.c_str(), GenericArgumentGroupAst::from_empty()); // todo
}

auto SPP::SemanticAnalysis::Asts::GenericIdentifierAst::empty() -> std::unique_ptr<GenericIdentifierAst> {
    return std::make_unique<GenericIdentifierAst>(0, "", GenericArgumentGroupAst::from_empty());
}

SPP::SemanticAnalysis::Asts::GenericIdentifierAst::~GenericIdentifierAst() = default;

auto SPP::SemanticAnalysis::Asts::GenericIdentifierAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        value,
        generic_args_group->print(printer));
    return string;
}
