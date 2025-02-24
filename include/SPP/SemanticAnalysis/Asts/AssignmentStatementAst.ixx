module;
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.assignment_statement_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct AssignmentStatementAst;
}


struct SPP::SemanticAnalysis::Asts::AssignmentStatementAst final : Ast {
    AstMemberType<std::vector<Ast>> lhs;
    AstMemberType<TokenAst> tok_assign;
    AstMemberType<std::vector<Ast>> rhs;

    AssignmentStatementAst(
        std::size_t pos,
        decltype(lhs) &&lhs,
        decltype(tok_assign) &&tok_assign,
        decltype(rhs) &&rhs);

    ~AssignmentStatementAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
