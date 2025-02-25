module;
#include <format>
#include <numeric>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.pattern_variant_destructure_tuple_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::PatternVariantDestructureTupleAst::PatternVariantDestructureTupleAst(
    const std::size_t pos,
    decltype(tok_left_parenthesis) &&tok_left_parenthesis,
    decltype(bindings) &&bindings,
    decltype(tok_right_parenthesis) &&tok_right_parenthesis):
    Ast{pos},
    tok_left_parenthesis{std::move(tok_left_parenthesis)},
    bindings{std::move(bindings)},
    tok_right_parenthesis{std::move(tok_right_parenthesis)} {
}

SPP::SemanticAnalysis::Asts::PatternVariantDestructureTupleAst::~PatternVariantDestructureTupleAst() = default;

auto SPP::SemanticAnalysis::Asts::PatternVariantDestructureTupleAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto bindings_string_1 = bindings | std::views::transform([&printer](auto const &binding) { return binding->print(printer); });
    auto bindings_string_2 = std::accumulate(bindings_string_1.begin(), bindings_string_1.end(), std::string{});

    auto string = std::format(
        "{}{}{}",
        tok_left_parenthesis->print(printer),
        std::move(bindings_string_2),
        tok_right_parenthesis->print(printer));
    return string;
}
