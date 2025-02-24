module;
#include <string>

export module spp.semantic_analysis.asts.postfix_expression_operator_early_return_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct PostfixExpressionOperatorEarlyReturnAst;
}


struct SPP::SemanticAnalysis::Asts::PostfixExpressionOperatorEarlyReturnAst final : Ast {
    AstMemberType<TokenAst> tok_question_mark;

    PostfixExpressionOperatorEarlyReturnAst(
        std::size_t pos,
        decltype(tok_question_mark) &&tok_question_mark);

    ~PostfixExpressionOperatorEarlyReturnAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
