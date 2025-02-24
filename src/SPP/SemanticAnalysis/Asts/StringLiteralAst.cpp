module;
#include <string>

module spp.semantic_analysis.asts.string_literal_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::StringLiteralAst::StringLiteralAst(
    const std::size_t pos,
    decltype(val) &&val):
    Ast{pos},
    val{std::move(val)} {
}


SPP::SemanticAnalysis::Asts::StringLiteralAst::~StringLiteralAst() = default;

auto SPP::SemanticAnalysis::Asts::StringLiteralAst::print(Meta::AstPrinter &printer) const -> std::string {
    return val->print(printer);
}

