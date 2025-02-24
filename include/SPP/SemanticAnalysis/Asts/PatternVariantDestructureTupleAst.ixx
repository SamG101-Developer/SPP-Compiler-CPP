module;
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.pattern_variant_destructure_tuple_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct PatternVariantDestructureTupleAst;
}


struct SPP::SemanticAnalysis::Asts::PatternVariantDestructureTupleAst final : Ast {
    AstMemberType<TokenAst> tok_left_parenthesis;
    AstMemberType<std::vector<Ast>> bindings;
    AstMemberType<TokenAst> tok_right_parenthesis;

    PatternVariantDestructureTupleAst(
        std::size_t pos,
        decltype(tok_left_parenthesis) &&tok_left_parenthesis,
        decltype(bindings) &&bindings,
        decltype(tok_right_parenthesis) &&tok_right_parenthesis);

    ~PatternVariantDestructureTupleAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
