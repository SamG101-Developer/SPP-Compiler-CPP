module;
#include <string>

export module spp.semantic_analysis.asts.pattern_variant_expression_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct PatternVariantExpressionAst;
}


struct SPP::SemanticAnalysis::Asts::PatternVariantExpressionAst final : Ast {
    AstMemberType<Ast> expr;

    PatternVariantExpressionAst(
        std::size_t pos,
        decltype(expr) &&expr);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
