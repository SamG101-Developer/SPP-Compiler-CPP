module;
#include <string>

export module spp.semantic_analysis.asts.pattern_variant_else_case_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct PatternVariantElseCaseAst;
}


struct SPP::SemanticAnalysis::Asts::PatternVariantElseCaseAst final : Ast {
    AstMemberType<TokenAst> tok_else;
    AstMemberType<CaseExpressionAst> case_expr;

    PatternVariantElseCaseAst(
        std::size_t pos,
        decltype(tok_else) &&tok_else,
        decltype(case_expr) &&case_expr);

    ~PatternVariantElseCaseAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
