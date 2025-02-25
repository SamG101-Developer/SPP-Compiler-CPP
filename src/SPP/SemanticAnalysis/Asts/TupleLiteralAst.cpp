module;
#include <format>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.tuple_literal_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::TupleLiteralAst::TupleLiteralAst(
    const std::size_t pos,
    decltype(tok_left_parenthesis) &&tok_left_parenthesis,
    decltype(tuple_list) &&tuple_list,
    decltype(tok_right_parenthesis) &&tok_right_parenthesis):
    Ast{pos},
    tok_left_parenthesis{std::move(tok_left_parenthesis)},
    tuple_list{std::move(tuple_list)},
    tok_right_parenthesis{std::move(tok_right_parenthesis)} {
}

SPP::SemanticAnalysis::Asts::TupleLiteralAst::~TupleLiteralAst() = default;

auto SPP::SemanticAnalysis::Asts::TupleLiteralAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto tuple_list_string_1 = tuple_list | std::views::transform([&printer](const auto &member) { return member->print(printer); });
    auto tuple_list_string_2 = std::string{tuple_list_string_1.begin(), tuple_list_string_1.end()};

    auto string = std::format(
        "{}{}{}",
        tok_left_parenthesis->print(printer),
        std::move(tuple_list_string_2),
        tok_right_parenthesis->print(printer));
    return string;
}
