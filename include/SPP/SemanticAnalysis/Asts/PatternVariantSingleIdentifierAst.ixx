module;
#include <string>

export module spp.semantic_analysis.asts.pattern_variant_single_identifier_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct PatternVariantSingleIdentifierAst;
}


struct SPP::SemanticAnalysis::Asts::PatternVariantSingleIdentifierAst final : Ast {
    AstMemberTypeOpt<TokenAst> tok_mut;
    AstMemberType<IdentifierAst> name;
    AstMemberTypeOpt<LocalVariableSingleIdentifierAliasAst> alias;

    PatternVariantSingleIdentifierAst(
        std::size_t pos,
        decltype(tok_mut) &&tok_mut,
        decltype(name) &&name,
        decltype(alias) &&alias);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
