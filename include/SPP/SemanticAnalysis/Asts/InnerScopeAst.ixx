module;
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.inner_scope_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct InnerScopeAst;
}


struct SPP::SemanticAnalysis::Asts::InnerScopeAst final : Ast {
    AstMemberType<TokenAst> tok_left_brace;
    AstMemberType<std::vector<StatementAst>> members;
    AstMemberType<TokenAst> tok_right_brace;

    InnerScopeAst(
        std::size_t pos,
        decltype(tok_left_brace) &&tok_left_brace,
        decltype(members) &&members,
        decltype(tok_right_brace) &&tok_right_brace);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
