module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.identifier_ast;


SPP::SemanticAnalysis::Asts::IdentifierAst::IdentifierAst(
    const std::size_t pos,
    decltype(value) &&value):
    Ast{pos},
    value{std::move(value)} {
}

SPP::SemanticAnalysis::Asts::IdentifierAst::~IdentifierAst() = default;

auto SPP::SemanticAnalysis::Asts::IdentifierAst::print(Meta::AstPrinter &printer) const -> std::string {
    return value;
}
