module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.postfix_expression_operator_early_return_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::PostfixExpressionOperatorEarlyReturnAst::PostfixExpressionOperatorEarlyReturnAst(
    const std::size_t pos,
    decltype(tok_question_mark) &&tok_question_mark):
    Ast{pos},
    tok_question_mark{std::move(tok_question_mark)} {
}

SPP::SemanticAnalysis::Asts::PostfixExpressionOperatorEarlyReturnAst::~PostfixExpressionOperatorEarlyReturnAst() = default;

auto SPP::SemanticAnalysis::Asts::PostfixExpressionOperatorEarlyReturnAst::print(Meta::AstPrinter &printer) const -> std::string {
    return tok_question_mark->print(printer);
}
