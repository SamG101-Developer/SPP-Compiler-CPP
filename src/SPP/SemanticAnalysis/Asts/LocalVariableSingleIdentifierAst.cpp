module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.local_variable_single_identifier_ast;
import spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.asts.identifier_ast;
import spp.semantic_analysis.asts.local_variable_single_identifier_alias_ast;


SPP::SemanticAnalysis::Asts::LocalVariableSingleIdentifierAst::LocalVariableSingleIdentifierAst(
    const std::size_t pos,
    decltype(tok_mut) &&tok_mut,
    decltype(name) &&name,
    decltype(alias) &&alias):
    Ast{pos},
    tok_mut{std::move(tok_mut)},
    name{std::move(name)},
    alias{std::move(alias)} {
}

SPP::SemanticAnalysis::Asts::LocalVariableSingleIdentifierAst::~LocalVariableSingleIdentifierAst() = default;

auto SPP::SemanticAnalysis::Asts::LocalVariableSingleIdentifierAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}",
        tok_mut.has_value() ? tok_mut.value()->print(printer) + " " : "",
        name->print(printer),
        alias.has_value() ? alias.value()->print(printer) : "");
    return string;
}
