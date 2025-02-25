module;
#include <format>
#include <numeric>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.inner_scope_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::InnerScopeAst::InnerScopeAst(
    const std::size_t pos,
    decltype(tok_left_brace) &&tok_left_brace,
    decltype(members) &&members,
    decltype(tok_right_brace) &&tok_right_brace):
    Ast{pos},
    tok_left_brace{std::move(tok_left_brace)},
    members{std::move(members)},
    tok_right_brace{std::move(tok_right_brace)} {
}

SPP::SemanticAnalysis::Asts::InnerScopeAst::~InnerScopeAst() = default;

auto SPP::SemanticAnalysis::Asts::InnerScopeAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto members_string_1 = members | std::views::transform([&printer](const auto &member) { return member->print(printer); });
    auto members_string_2 = std::accumulate(members_string_1.begin(), members_string_1.end(), std::string{});

    auto string = std::format(
        "{}{}{}",
        tok_left_brace->print(printer),
        std::move(members_string_2),
        tok_right_brace->print(printer));
    return string;
}
