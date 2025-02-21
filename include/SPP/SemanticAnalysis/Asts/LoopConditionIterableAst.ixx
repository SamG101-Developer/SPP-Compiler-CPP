module;
#include <memory>
#include <string>

export module spp.semantic_analysis.asts.loop_condition_iterable_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct LoopConditionIterableAst;
}


struct SPP::SemanticAnalysis::Asts::LoopConditionIterableAst final : Ast {
    AstMemberType<LocalVariableAst> variable;
    AstMemberType<TokenAst> tok_in;
    AstMemberType<ExpressionAst> iterable;

    LoopConditionIterableAst(
        std::size_t pos,
        decltype(variable) &&variable,
        decltype(tok_in) &&tok_in,
        decltype(iterable) &&iterable);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
