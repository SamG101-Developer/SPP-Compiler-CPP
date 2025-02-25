module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.generic_comp_argument_unnamed_ast;


SPP::SemanticAnalysis::Asts::GenericCompArgumentUnnamedAst::GenericCompArgumentUnnamedAst(
    const std::size_t pos,
    decltype(value) &&value):
    Ast{pos},
    value{std::move(value)} {
}

SPP::SemanticAnalysis::Asts::GenericCompArgumentUnnamedAst::~GenericCompArgumentUnnamedAst() = default;

auto SPP::SemanticAnalysis::Asts::GenericCompArgumentUnnamedAst::print(Meta::AstPrinter &printer) const -> std::string {
    return value->print(printer);
}
