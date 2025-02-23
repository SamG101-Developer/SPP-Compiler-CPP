module;
#include <string>

export module spp.semantic_analysis.asts.postfix_expression_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct PostfixExpressionAst;
}


struct SPP::SemanticAnalysis::Asts::PostfixExpressionAst final : Ast {
    AstMemberType<Ast> lhs;
    AstMemberType<Ast> op;

    PostfixExpressionAst(
        std::size_t pos,
        decltype(lhs) &&lhs,
        decltype(op) &&op);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
