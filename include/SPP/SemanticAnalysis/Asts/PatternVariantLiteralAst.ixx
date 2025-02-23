module;
#include <string>

export module spp.semantic_analysis.asts.pattern_variant_literal_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct PatternVariantLiteralAst;
}


struct SPP::SemanticAnalysis::Asts::PatternVariantLiteralAst final : Ast {
    AstMemberType<Ast> literal;

    PatternVariantLiteralAst(
        std::size_t pos,
        decltype(literal) &&literal);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
