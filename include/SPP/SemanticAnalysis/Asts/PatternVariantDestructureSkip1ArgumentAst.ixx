module;
#include <string>

export module spp.semantic_analysis.asts.pattern_variant_destructure_skip_1_argument_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct PatternVariantDestructureSkip1ArgumentAst;
}


struct SPP::SemanticAnalysis::Asts::PatternVariantDestructureSkip1ArgumentAst final : Ast {
    AstMemberType<TokenAst> tok_underscore;

    PatternVariantDestructureSkip1ArgumentAst(
        std::size_t pos,
        decltype(tok_underscore) &&tok_underscore);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
