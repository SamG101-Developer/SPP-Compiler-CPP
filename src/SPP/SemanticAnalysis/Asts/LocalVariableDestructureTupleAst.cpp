module;
#include <format>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.local_variable_destructure_tuple_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::LocalVariableDestructureTupleAst::LocalVariableDestructureTupleAst(
    const std::size_t pos,
    decltype(tok_left_parenthesis) &&tok_left_parenthesis,
    decltype(bindings) &&bindings,
    decltype(tok_right_parenthesis) &&tok_right_parenthesis):
    Ast{pos},
    tok_left_parenthesis{std::move(tok_left_parenthesis)},
    bindings{std::move(bindings)},
    tok_right_parenthesis{std::move(tok_right_parenthesis)} {
}

SPP::SemanticAnalysis::Asts::LocalVariableDestructureTupleAst::~LocalVariableDestructureTupleAst() = default;

auto SPP::SemanticAnalysis::Asts::LocalVariableDestructureTupleAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto bindings_string_1 = bindings | std::views::transform([&printer](const auto &member) { return member->print(printer); });
    auto bindings_string_2 = std::string{bindings_string_1.begin(), bindings_string_1.end()};

    auto string = std::format(
        "{}{}{}",
        tok_left_parenthesis->print(printer),
        std::move(bindings_string_2),
        tok_right_parenthesis->print(printer));
    return string;
}
