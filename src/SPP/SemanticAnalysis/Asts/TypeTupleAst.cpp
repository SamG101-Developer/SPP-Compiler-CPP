module;
#include <format>
#include <numeric>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.type_tuple_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::TypeTupleAst::TypeTupleAst(
    const std::size_t pos,
    decltype(tok_left_parenthesis) &&tok_left_parenthesis,
    decltype(type_list) &&type_list,
    decltype(tok_right_parenthesis) &&tok_right_parenthesis):
    Ast{pos},
    tok_left_parenthesis{std::move(tok_left_parenthesis)},
    type_list{std::move(type_list)},
    tok_right_parenthesis{std::move(tok_right_parenthesis)} {
}

SPP::SemanticAnalysis::Asts::TypeTupleAst::~TypeTupleAst() = default;

auto SPP::SemanticAnalysis::Asts::TypeTupleAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto type_list_string_1 = type_list | std::views::transform([&printer](const auto &member) { return member->print(printer); });
    auto type_list_string_2 = std::accumulate(type_list_string_1.begin(), type_list_string_1.end(), std::string{});

    auto string = std::format(
        "{}{}{}",
        tok_left_parenthesis->print(printer),
        std::move(type_list_string_2),
        tok_right_parenthesis->print(printer));
    return string;
}
