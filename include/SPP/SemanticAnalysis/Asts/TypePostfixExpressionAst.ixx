module;
#include <string>

export module spp.semantic_analysis.asts.type_postfix_expression_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct TypePostfixExpressionAst;
}


struct SPP::SemanticAnalysis::Asts::TypePostfixExpressionAst final : Ast {
    AstMemberType<Ast> lhs;
    AstMemberType<Ast> op;

    TypePostfixExpressionAst(
        std::size_t pos,
        decltype(lhs) &&lhs,
        decltype(op) &&op);

    ~TypePostfixExpressionAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
