module;
#include <string>

export module spp.semantic_analysis.asts.loop_else_statement_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct LoopElseStatementAst;
}


struct SPP::SemanticAnalysis::Asts::LoopElseStatementAst final : Ast {
    AstMemberType<TokenAst> tok_else;
    AstMemberType<InnerScopeAst> body;

    LoopElseStatementAst(
        std::size_t pos,
        decltype(tok_else) &&tok_else,
        decltype(body) &&body);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
