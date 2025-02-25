module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.postfix_expression_operator_step_keyword_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::PostfixExpressionOperatorStepKeywordAst::PostfixExpressionOperatorStepKeywordAst(
    const std::size_t pos,
    decltype(tok_dot) &&tok_dot,
    decltype(tok_step) &&tok_step):
    Ast{pos},
    tok_dot{std::move(tok_dot)},
    tok_step{std::move(tok_step)} {
}

SPP::SemanticAnalysis::Asts::PostfixExpressionOperatorStepKeywordAst::~PostfixExpressionOperatorStepKeywordAst() = default;

auto SPP::SemanticAnalysis::Asts::PostfixExpressionOperatorStepKeywordAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        tok_dot->print(printer),
        tok_step->print(printer));
    return string;
}
