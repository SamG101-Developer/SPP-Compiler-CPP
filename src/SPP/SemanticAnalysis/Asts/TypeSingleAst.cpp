module;
#include <memory>
#include <string>

module spp.semantic_analysis.asts.type_single_ast;
import spp.semantic_analysis.asts.generic_identifier_ast;
import spp.semantic_analysis.asts.identifier_ast;


SPP::SemanticAnalysis::Asts::TypeSingleAst::TypeSingleAst(
    const std::size_t pos,
    decltype(name) &&name):
    Ast{pos},
    name{std::move(name)} {
}

auto SPP::SemanticAnalysis::Asts::TypeSingleAst::from(IdentifierAst const &identifier) -> std::unique_ptr<TypeSingleAst> {
    return std::make_unique<TypeSingleAst>(identifier.pos, GenericIdentifierAst::from(identifier));
}

auto SPP::SemanticAnalysis::Asts::TypeSingleAst::from(GenericIdentifierAst const &identifier) -> std::unique_ptr<TypeSingleAst> {
    return std::make_unique<TypeSingleAst>(identifier.pos, GenericIdentifierAst::from(identifier));
}

SPP::SemanticAnalysis::Asts::TypeSingleAst::~TypeSingleAst() = default;

auto SPP::SemanticAnalysis::Asts::TypeSingleAst::print(Meta::AstPrinter &printer) const -> std::string {
    return name->print(printer);
}
