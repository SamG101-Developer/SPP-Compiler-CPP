module;
#include <format>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.case_expression_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::CaseExpressionAst::CaseExpressionAst(
    const std::size_t pos,
    decltype(tok_case) &&tok_case,
    decltype(expr) &&expr,
    decltype(tok_of) &&tok_of,
    decltype(branches) &&branches):
    Ast{pos},
    tok_case{std::move(tok_case)},
    expr{std::move(expr)},
    tok_of{std::move(tok_of)},
    branches{std::move(branches)} {
}

SPP::SemanticAnalysis::Asts::CaseExpressionAst::~CaseExpressionAst() = default;

auto SPP::SemanticAnalysis::Asts::CaseExpressionAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{} {} {} {}",
        tok_case->print(printer),
        expr->print(printer),
        tok_of.has_value() ? tok_of.value()->print(printer) : "",
        branches | std::ranges::views::transform([&printer](const auto &element) { return element->print(printer); }) | std::ranges::to<std::string>);
    return string;
}
