module;
#include <string>

export module spp.semantic_analysis.asts.postfix_expression_operator_step_keyword_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct PostfixExpressionOperatorStepKeywordAst;
}


struct SPP::SemanticAnalysis::Asts::PostfixExpressionOperatorStepKeywordAst final : Ast {
    AstMemberType<TokenAst> tok_dot;
    AstMemberType<TokenAst> tok_step;

    PostfixExpressionOperatorStepKeywordAst(
        std::size_t pos,
        decltype(tok_dot) &&tok_dot,
        decltype(tok_step) &&tok_step);

    ~PostfixExpressionOperatorStepKeywordAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
