module;
#include <string>

export module spp.semantic_analysis.asts.type_array_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct TypeArrayAst;
}


struct SPP::SemanticAnalysis::Asts::TypeArrayAst final : Ast {
    AstMemberType<TokenAst> tok_left_bracket;
    AstMemberType<Ast> type;
    AstMemberType<TokenAst> tok_comma;
    AstMemberType<TokenAst> size;
    AstMemberType<TokenAst> tok_right_bracket;

    TypeArrayAst(
        std::size_t pos,
        decltype(tok_left_bracket) &&tok_left_bracket,
        decltype(type) &&type,
        decltype(tok_comma) &&tok_comma,
        decltype(size) &&size,
        decltype(tok_right_bracket) &&tok_right_bracket);

    ~TypeArrayAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;

    auto convert() -> AstMemberType<Ast>;
};
