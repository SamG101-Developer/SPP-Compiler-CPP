module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.type_postfix_operator_nested_type_ast;
import spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.asts.type_single_ast;


SPP::SemanticAnalysis::Asts::TypePostfixOperatorNestedTypeAst::TypePostfixOperatorNestedTypeAst(
    const std::size_t pos,
    decltype(tok_sep) &&tok_sep,
    decltype(name) &&name):
    Ast{pos},
    tok_sep{std::move(tok_sep)},
    name{std::move(name)} {
}

SPP::SemanticAnalysis::Asts::TypePostfixOperatorNestedTypeAst::~TypePostfixOperatorNestedTypeAst() = default;

auto SPP::SemanticAnalysis::Asts::TypePostfixOperatorNestedTypeAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        tok_sep->print(printer),
        name->print(printer));
    return string;
}
