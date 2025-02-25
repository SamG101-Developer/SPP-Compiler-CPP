module;
#include <format>
#include <numeric>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.sup_implementation_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::SupImplementationAst::SupImplementationAst(
    const std::size_t pos,
    decltype(tok_brace_l) &&tok_brace_l,
    decltype(members) &&members,
    decltype(tok_brace_r) &&tok_brace_r):
    Ast{pos},
    tok_brace_l{std::move(tok_brace_l)},
    members{std::move(members)},
    tok_brace_r{std::move(tok_brace_r)} {
}

SPP::SemanticAnalysis::Asts::SupImplementationAst::~SupImplementationAst() = default;

auto SPP::SemanticAnalysis::Asts::SupImplementationAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto members_string_1 = members | std::views::transform([&printer](const auto &member) { return member->print(printer); });
    auto members_string_2 = std::accumulate(members_string_1.begin(), members_string_1.end(), std::string{});

    auto string = std::format(
        "{}{}{}",
        tok_brace_l->print(printer),
        std::move(members_string_2),
        tok_brace_r->print(printer));
    return string;
}
