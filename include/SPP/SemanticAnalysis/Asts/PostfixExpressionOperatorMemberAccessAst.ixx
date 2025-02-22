module;
#include <string>

export module spp.semantic_analysis.asts.postfix_expression_operator_member_access_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct PostfixExpressionOperatorMemberAccessAst;
}


struct SPP::SemanticAnalysis::Asts::PostfixExpressionOperatorMemberAccessAst final : Ast {
    AstMemberType<TokenAst> tok_access;
    AstMemberType<PostfixExpressionOperatorMemberAccessFieldIdentifierAst> field;

    PostfixExpressionOperatorMemberAccessAst(
        std::size_t pos,
        decltype(tok_access) &&tok_access,
        decltype(field) &&field);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
