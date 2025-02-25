module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.generic_type_argument_unnamed_ast;


SPP::SemanticAnalysis::Asts::GenericTypeArgumentUnnamedAst::GenericTypeArgumentUnnamedAst(
    const std::size_t pos,
    decltype(type) &&type):
    Ast{pos},
    type{std::move(type)} {
}

SPP::SemanticAnalysis::Asts::GenericTypeArgumentUnnamedAst::~GenericTypeArgumentUnnamedAst() = default;

auto SPP::SemanticAnalysis::Asts::GenericTypeArgumentUnnamedAst::print(Meta::AstPrinter &printer) const -> std::string {
    return type->print(printer);
}
