module;
#include <memory>
#include <string>

export module spp.semantic_analysis.asts.parenthesized_expression_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct ParenthesizedExpressionAst;
}


struct SPP::SemanticAnalysis::Asts::ParenthesizedExpressionAst final : Ast {
    AstMemberType<TokenAst> tok_left_parenthesis;
    AstMemberType<Ast> expr;
    AstMemberType<TokenAst> tok_right_parenthesis;

    ParenthesizedExpressionAst(
        std::size_t pos,
        decltype(tok_left_parenthesis) &&tok_left_parenthesis,
        decltype(expr) &&expr,
        decltype(tok_right_parenthesis) &&tok_right_parenthesis);

    ~ParenthesizedExpressionAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
