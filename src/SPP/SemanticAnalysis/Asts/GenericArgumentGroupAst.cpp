module;
#include <format>
#include <numeric>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.generic_argument_group_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::GenericArgumentGroupAst::GenericArgumentGroupAst(
    const std::size_t pos,
    decltype(tok_paren_l) &&tok_paren_l,
    decltype(members) &&members,
    decltype(tok_paren_r) &&tok_paren_r):
    Ast{pos},
    tok_paren_l{std::move(tok_paren_l)},
    members{std::move(members)},
    tok_paren_r{std::move(tok_paren_r)} {
}

SPP::SemanticAnalysis::Asts::GenericArgumentGroupAst::~GenericArgumentGroupAst() = default;

auto SPP::SemanticAnalysis::Asts::GenericArgumentGroupAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto members_string_1 = members | std::views::transform([&printer](auto const &member) { return member->print(printer); });
    auto members_string_2 = std::accumulate(members_string_1.begin(), members_string_1.end(), std::string{});

    auto string = std::format(
        "{}{}{}",
        tok_paren_l->print(printer),
        std::move(members_string_2),
        tok_paren_r->print(printer));
    return string;
}
