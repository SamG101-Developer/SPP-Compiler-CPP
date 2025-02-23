module;
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.loop_control_flow_statement_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct LoopControlFlowStatementAst;
}


struct SPP::SemanticAnalysis::Asts::LoopControlFlowStatementAst final : Ast {
    AstMemberType<std::vector<TokenAst>> tok_loop;
    AstMemberTypeOpt<LoopControlFlowFinalActionAst> skip_or_expr;

    LoopControlFlowStatementAst(
        std::size_t pos,
        decltype(tok_loop) &&tok_loop,
        decltype(skip_or_expr) &&skip_or_expr);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
