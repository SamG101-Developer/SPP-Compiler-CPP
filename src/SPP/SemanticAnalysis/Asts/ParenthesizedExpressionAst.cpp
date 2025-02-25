module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.parenthesized_expression_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::ParenthesizedExpressionAst::ParenthesizedExpressionAst(
    const std::size_t pos,
    decltype(tok_left_parenthesis) &&tok_left_parenthesis,
    decltype(expr) &&expr,
    decltype(tok_right_parenthesis) &&tok_right_parenthesis):
    Ast{pos},
    tok_left_parenthesis{std::move(tok_left_parenthesis)},
    expr{std::move(expr)},
    tok_right_parenthesis{std::move(tok_right_parenthesis)} {
}

SPP::SemanticAnalysis::Asts::ParenthesizedExpressionAst::~ParenthesizedExpressionAst() = default;

auto SPP::SemanticAnalysis::Asts::ParenthesizedExpressionAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}",
        tok_left_parenthesis->print(printer),
        expr->print(printer),
        tok_right_parenthesis->print(printer));
    return string;
}
