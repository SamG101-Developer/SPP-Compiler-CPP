module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.postfix_expression_ast;


SPP::SemanticAnalysis::Asts::PostfixExpressionAst::PostfixExpressionAst(
    const std::size_t pos,
    decltype(lhs) &&lhs,
    decltype(op) &&op):
    Ast{pos},
    lhs{std::move(lhs)},
    op{std::move(op)} {
}

SPP::SemanticAnalysis::Asts::PostfixExpressionAst::~PostfixExpressionAst() = default;

auto SPP::SemanticAnalysis::Asts::PostfixExpressionAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        lhs->print(printer),
        op->print(printer));
    return string;
}
