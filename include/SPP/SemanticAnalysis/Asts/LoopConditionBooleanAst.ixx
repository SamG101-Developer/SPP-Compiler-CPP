module;
#include <string>

export module spp.semantic_analysis.asts.loop_condition_boolean_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct LoopConditionBooleanAst;
}


struct SPP::SemanticAnalysis::Asts::LoopConditionBooleanAst final : Ast {
    AstMemberType<Ast> cond;

    LoopConditionBooleanAst(
        std::size_t pos,
        decltype(cond) &&cond);

    ~LoopConditionBooleanAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
