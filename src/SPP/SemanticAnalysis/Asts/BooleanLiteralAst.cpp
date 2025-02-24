module;
#include <string>

module spp.semantic_analysis.asts.boolean_literal_ast;
import spp.semantic_analysis.asts.token_ast;

SPP::SemanticAnalysis::Asts::BooleanLiteralAst::BooleanLiteralAst(
    const std::size_t pos,
    decltype(val) &&val):
    Ast{pos},
    val{std::move(val)} {
}

SPP::SemanticAnalysis::Asts::BooleanLiteralAst::~BooleanLiteralAst() = default;

auto SPP::SemanticAnalysis::Asts::BooleanLiteralAst::print(Meta::AstPrinter &printer) const -> std::string {
    return val->print(printer);
}
