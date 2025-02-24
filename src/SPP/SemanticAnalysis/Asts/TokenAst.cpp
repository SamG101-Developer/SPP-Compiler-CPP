module;
#include <cstddef>

module spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::TokenAst::TokenAst(
    const std::size_t pos,
    const decltype(token_type) token_type,
    decltype(token_data) &&token_data):
    Ast{pos},
    token_type{token_type},
    token_data{std::move(token_data)} {
}


SPP::SemanticAnalysis::Asts::TokenAst::~TokenAst() = default;

auto SPP::SemanticAnalysis::Asts::TokenAst::print(Meta::AstPrinter &printer) const -> std::string {
    return token_data;
}
