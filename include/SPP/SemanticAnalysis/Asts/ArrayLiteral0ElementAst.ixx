module;
#include <string>

export module spp.semantic_analysis.asts.array_literal_0_element_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct ArrayLiteral0ElementAst;
}


struct SPP::SemanticAnalysis::Asts::ArrayLiteral0ElementAst final : Ast {
    AstMemberType<TokenAst> tok_left_bracket;
    AstMemberType<Ast> elem_type;
    AstMemberType<TokenAst> tok_comma;
    AstMemberType<TokenAst> size;
    AstMemberType<TokenAst> tok_right_bracket;

    ArrayLiteral0ElementAst(
        std::size_t pos,
        decltype(tok_left_bracket) &&tok_left_bracket,
        decltype(elem_type) &&elem_type,
        decltype(tok_comma) &&tok_comma,
        decltype(size) &&size,
        decltype(tok_right_bracket) &&tok_right_bracket);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
