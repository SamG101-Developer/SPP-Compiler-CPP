module;
#include <string>

export module spp.semantic_analysis.asts.type_binary_expression_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct TypeBinaryExpressionAst;
}


struct SPP::SemanticAnalysis::Asts::TypeBinaryExpressionAst final : Ast {
    AstMemberType<TypeAst> lhs;
    AstMemberType<TokenAst> op;
    AstMemberType<TypeAst> rhs;

    TypeBinaryExpressionAst(
        std::size_t pos,
        decltype(lhs) &&lhs,
        decltype(op) &&op,
        decltype(rhs) &&rhs);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;

    auto convert() -> AstMemberType<TypeAst>;
};
