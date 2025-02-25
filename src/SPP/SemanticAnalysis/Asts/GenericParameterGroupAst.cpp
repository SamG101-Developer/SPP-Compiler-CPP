module;
#include <format>
#include <numeric>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.generic_parameter_group_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::GenericParameterGroupAst::GenericParameterGroupAst(
    const std::size_t pos,
    decltype(tok_left_parenthesis) &&tok_left_parenthesis,
    decltype(generic_args_groups) &&generic_args_groups,
    decltype(tok_right_parenthesis) &&tok_right_parenthesis):
    Ast{pos},
    tok_left_parenthesis{std::move(tok_left_parenthesis)},
    generic_args_groups{std::move(generic_args_groups)},
    tok_right_parenthesis{std::move(tok_right_parenthesis)} {
}

SPP::SemanticAnalysis::Asts::GenericParameterGroupAst::~GenericParameterGroupAst() = default;

auto SPP::SemanticAnalysis::Asts::GenericParameterGroupAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto generic_args_groups_string_1 = generic_args_groups | std::views::transform([&printer](auto const &generic_args_group) { return generic_args_group->print(printer); });
    auto generic_args_groups_string_2 = std::accumulate(generic_args_groups_string_1.begin(), generic_args_groups_string_1.end(), std::string{});

    auto string = std::format(
        "{}{}{}",
        tok_left_parenthesis->print(printer),
        std::move(generic_args_groups_string_2),
        tok_right_parenthesis->print(printer));
    return string;
}
