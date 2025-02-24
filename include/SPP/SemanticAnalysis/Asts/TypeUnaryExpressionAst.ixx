module;
#include <string>

export module spp.semantic_analysis.asts.type_unary_expression_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct TypeUnaryExpressionAst;
}


struct SPP::SemanticAnalysis::Asts::TypeUnaryExpressionAst final : Ast {
    AstMemberType<Ast> op;
    AstMemberType<Ast> rhs;

    TypeUnaryExpressionAst(
        std::size_t pos,
        decltype(op) &&op,
        decltype(rhs) &&rhs);

    ~TypeUnaryExpressionAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
