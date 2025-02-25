module;
#include <format>
#include <numeric>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.local_variable_destructure_array_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::LocalVariableDestructureArrayAst::LocalVariableDestructureArrayAst(
    const std::size_t pos,
    decltype(tok_left_bracket) &&tok_left_bracket,
    decltype(bindings) &&bindings,
    decltype(tok_right_bracket) &&tok_right_bracket):
    Ast{pos},
    tok_left_bracket{std::move(tok_left_bracket)},
    bindings{std::move(bindings)},
    tok_right_bracket{std::move(tok_right_bracket)} {
}

SPP::SemanticAnalysis::Asts::LocalVariableDestructureArrayAst::~LocalVariableDestructureArrayAst() = default;

auto SPP::SemanticAnalysis::Asts::LocalVariableDestructureArrayAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto bindings_string_1 = bindings | std::views::transform([&printer](auto const &binding) { return binding->print(printer); });
    auto bindings_string_2 = std::accumulate(bindings_string_1.begin(), bindings_string_1.end(), std::string{});

    auto string = std::format(
        "{}{}{}",
        tok_left_bracket->print(printer),
        std::move(bindings_string_2),
        tok_right_bracket->print(printer));
    return string;
}
