module;
#include <format>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.case_expression_branch_ast;
import spp.semantic_analysis.asts.pattern_guard_ast;
import spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.asts.inner_scope_ast;

SPP::SemanticAnalysis::Asts::CaseExpressionBranchAst::CaseExpressionBranchAst(
    const std::size_t pos,
    decltype(comp_op) &&comp_op,
    decltype(patterns) &&patterns,
    decltype(guard) &&guard,
    decltype(body) &&body):
    Ast{pos},
    comp_op{std::move(comp_op)},
    patterns{std::move(patterns)},
    guard{std::move(guard)},
    body{std::move(body)} {
}

SPP::SemanticAnalysis::Asts::CaseExpressionBranchAst::~CaseExpressionBranchAst() = default;

auto SPP::SemanticAnalysis::Asts::CaseExpressionBranchAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto patterns_string_1 = patterns | std::ranges::views::transform([&printer](const auto &element) { return element->print(printer); });
    auto patterns_string_2 = std::string{patterns_string_1.begin(), patterns_string_1.end()};

    auto string = std::format(
        "{} {} {} {}",
        comp_op.has_value() ? comp_op.value()->print(printer) : "",
        std::move(patterns_string_2),
        guard.has_value() ? guard.value()->print(printer) : "",
        body->print(printer));
    return string;
}
