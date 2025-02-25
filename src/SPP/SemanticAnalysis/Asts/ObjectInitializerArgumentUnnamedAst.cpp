module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.object_initializer_argument_unnamed_ast;
import spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.asts.identifier_ast;


SPP::SemanticAnalysis::Asts::ObjectInitializerArgumentUnnamedAst::ObjectInitializerArgumentUnnamedAst(
    const std::size_t pos,
    decltype(tok_default) &&tok_default,
    decltype(name) &&name):
    Ast{pos},
    tok_default{std::move(tok_default)},
    name{std::move(name)} {
}

SPP::SemanticAnalysis::Asts::ObjectInitializerArgumentUnnamedAst::~ObjectInitializerArgumentUnnamedAst() = default;

auto SPP::SemanticAnalysis::Asts::ObjectInitializerArgumentUnnamedAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        tok_default.has_value() ? tok_default.value()->print(printer) : "",
        name->print(printer));
    return string;
}
