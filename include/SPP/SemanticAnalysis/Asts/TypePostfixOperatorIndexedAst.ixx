module;
#include <string>

export module spp.semantic_analysis.asts.type_postfix_operator_indexed_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct TypePostfixOperatorIndexedAst;
}


struct SPP::SemanticAnalysis::Asts::TypePostfixOperatorIndexedAst final : Ast {
    AstMemberType<TokenAst> tok_sep;
    AstMemberType<TokenAst> index;

    TypePostfixOperatorIndexedAst(
        std::size_t pos,
        decltype(tok_sep) &&tok_sep,
        decltype(index) &&index);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
