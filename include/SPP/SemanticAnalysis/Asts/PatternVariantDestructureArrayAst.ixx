module;
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.pattern_variant_destructure_array_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct PatternVariantDestructureArrayAst;
}


struct SPP::SemanticAnalysis::Asts::PatternVariantDestructureArrayAst final : Ast {
    AstMemberType<TokenAst> tok_left_bracket;
    AstMemberType<std::vector<Ast>> bindings;
    AstMemberType<TokenAst> tok_right_bracket;

    PatternVariantDestructureArrayAst(
        std::size_t pos,
        decltype(tok_left_bracket) &&tok_left_bracket,
        decltype(bindings) &&bindings,
        decltype(tok_right_bracket) &&tok_right_bracket);

    ~PatternVariantDestructureArrayAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
