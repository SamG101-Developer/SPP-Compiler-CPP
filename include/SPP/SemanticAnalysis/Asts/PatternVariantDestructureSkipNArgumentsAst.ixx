module;
#include <string>

export module spp.semantic_analysis.asts.pattern_variant_destructure_skip_n_arguments_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct PatternVariantDestructureSkipNArgumentsAst;
}


struct SPP::SemanticAnalysis::Asts::PatternVariantDestructureSkipNArgumentsAst final : Ast {
    AstMemberType<TokenAst> tok_variadic;
    AstMemberTypeOpt<PatternVariantSingleIdentifierAst> binding;

    PatternVariantDestructureSkipNArgumentsAst(
        std::size_t pos,
        decltype(tok_variadic) &&tok_variadic,
        decltype(binding) &&binding);

    ~PatternVariantDestructureSkipNArgumentsAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
