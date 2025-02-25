module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.postfix_expression_operator_not_keyword_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::PostfixExpressionOperatorNotKeywordAst::PostfixExpressionOperatorNotKeywordAst(
    const std::size_t pos,
    decltype(tok_dot) &&tok_dot,
    decltype(tok_not) &&tok_not):
    Ast{pos},
    tok_dot{std::move(tok_dot)},
    tok_not{std::move(tok_not)} {
}

SPP::SemanticAnalysis::Asts::PostfixExpressionOperatorNotKeywordAst::~PostfixExpressionOperatorNotKeywordAst() = default;

auto SPP::SemanticAnalysis::Asts::PostfixExpressionOperatorNotKeywordAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        tok_dot->print(printer),
        tok_not->print(printer));
    return string;
}
