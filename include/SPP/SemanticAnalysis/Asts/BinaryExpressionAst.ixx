module;
#include <string>

export module spp.semantic_analysis.asts.binary_expression_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct BinaryExpressionAst;
}


struct SPP::SemanticAnalysis::Asts::BinaryExpressionAst final : Ast {
    AstMemberType<Ast> lhs;
    AstMemberType<TokenAst> op;
    AstMemberType<Ast> rhs;

    BinaryExpressionAst(
        std::size_t pos,
        decltype(lhs) &&lhs,
        decltype(op) &&op,
        decltype(rhs) &&rhs);

    ~BinaryExpressionAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;

    auto convert() -> AstMemberType<Ast>;
};
