module;
#include <memory>
#include <string>

export module spp.semantic_analysis.asts.generic_type_parameter_inline_constraints_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct GenericTypeParameterInlineConstraintsAst;
}


struct SPP::SemanticAnalysis::Asts::GenericTypeParameterInlineConstraintsAst final : Ast {
    AstMemberType<TokenAst> tok_colon;
    AstMemberType<Ast> type;

    GenericTypeParameterInlineConstraintsAst(
        std::size_t pos,
        decltype(tok_colon) &&tok_colon,
        decltype(type) &&type);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
