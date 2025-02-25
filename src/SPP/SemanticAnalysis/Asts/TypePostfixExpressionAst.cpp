module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.type_postfix_expression_ast;


SPP::SemanticAnalysis::Asts::TypePostfixExpressionAst::TypePostfixExpressionAst(
    const std::size_t pos,
    decltype(lhs) &&lhs,
    decltype(op) &&op):
    Ast{pos},
    lhs{std::move(lhs)},
    op{std::move(op)} {
}

SPP::SemanticAnalysis::Asts::TypePostfixExpressionAst::~TypePostfixExpressionAst() = default;

auto SPP::SemanticAnalysis::Asts::TypePostfixExpressionAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        lhs->print(printer),
        op->print(printer));
    return string;
}
