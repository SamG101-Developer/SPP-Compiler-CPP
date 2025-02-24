module;
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.rel_statement_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct RelStatementAst;
}


struct SPP::SemanticAnalysis::Asts::RelStatementAst final : Ast {
    AstMemberType<TokenAst> tok_rel;
    AstMemberType<std::vector<Ast>> rels;

    RelStatementAst(
        std::size_t pos,
        decltype(tok_rel) &&tok_rel,
        decltype(rels) &&rels);

    ~RelStatementAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
