module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.loop_condition_iterable_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::LoopConditionIterableAst::LoopConditionIterableAst(
    const std::size_t pos,
    decltype(variable) &&variable,
    decltype(tok_in) &&tok_in,
    decltype(iterable) &&iterable):
    Ast{pos},
    variable{std::move(variable)},
    tok_in{std::move(tok_in)},
    iterable{std::move(iterable)} {
}

SPP::SemanticAnalysis::Asts::LoopConditionIterableAst::~LoopConditionIterableAst() = default;

auto SPP::SemanticAnalysis::Asts::LoopConditionIterableAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}",
        variable->print(printer),
        tok_in->print(printer),
        iterable->print(printer));
    return string;
}
