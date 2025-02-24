module;
#include <string>

export module spp.semantic_analysis.asts.unary_expression_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct UnaryExpressionAst;
}


struct SPP::SemanticAnalysis::Asts::UnaryExpressionAst final : Ast {
    AstMemberType<Ast> op;
    AstMemberType<Ast> rhs;

    UnaryExpressionAst(
        std::size_t pos,
        decltype(op) &&op,
        decltype(rhs) &&rhs);

    ~UnaryExpressionAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
