module;
#include <string>

export module spp.semantic_analysis.asts.postfix_expression_operator_not_keyword_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct PostfixExpressionOperatorNotKeywordAst;
}


struct SPP::SemanticAnalysis::Asts::PostfixExpressionOperatorNotKeywordAst final : Ast {
    AstMemberType<TokenAst> tok_dot;
    AstMemberType<TokenAst> tok_not;

    PostfixExpressionOperatorNotKeywordAst(
        std::size_t pos,
        decltype(tok_dot) &&tok_dot,
        decltype(tok_not) &&tok_not);

    ~PostfixExpressionOperatorNotKeywordAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
