module;
#include <string>

export module spp.semantic_analysis.asts.pattern_variant_else_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct PatternVariantElseAst;
}


struct SPP::SemanticAnalysis::Asts::PatternVariantElseAst final : Ast {
    AstMemberType<TokenAst> tok_else;

    PatternVariantElseAst(
        std::size_t pos,
        decltype(tok_else) &&tok_else);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
