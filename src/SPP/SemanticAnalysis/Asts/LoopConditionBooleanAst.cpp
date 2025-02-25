module;
#include <string>

module spp.semantic_analysis.asts.loop_condition_boolean_ast;


SPP::SemanticAnalysis::Asts::LoopConditionBooleanAst::LoopConditionBooleanAst(
    const std::size_t pos,
    decltype(cond) &&cond):
    Ast{pos},
    cond{std::move(cond)} {
}

SPP::SemanticAnalysis::Asts::LoopConditionBooleanAst::~LoopConditionBooleanAst() = default;

auto SPP::SemanticAnalysis::Asts::LoopConditionBooleanAst::print(Meta::AstPrinter &printer) const -> std::string {
    return cond->print(printer);
}
