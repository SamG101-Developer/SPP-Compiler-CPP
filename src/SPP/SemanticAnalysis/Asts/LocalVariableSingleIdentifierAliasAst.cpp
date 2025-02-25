module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.local_variable_single_identifier_alias_ast;
import spp.semantic_analysis.asts.identifier_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::LocalVariableSingleIdentifierAliasAst::LocalVariableSingleIdentifierAliasAst(
    const std::size_t pos,
    decltype(tok_as) &&tok_as,
    decltype(name) &&name):
    Ast{pos},
    tok_as{std::move(tok_as)},
    name{std::move(name)} {
}

SPP::SemanticAnalysis::Asts::LocalVariableSingleIdentifierAliasAst::~LocalVariableSingleIdentifierAliasAst() = default;

auto SPP::SemanticAnalysis::Asts::LocalVariableSingleIdentifierAliasAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        tok_as->print(printer),
        name->print(printer));
    return string;
}
