module;
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.type_tuple_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct TypeTupleAst;
}


struct SPP::SemanticAnalysis::Asts::TypeTupleAst final : Ast {
    AstMemberType<TokenAst> tok_left_parenthesis;
    AstMemberType<std::vector<Ast>> type_list;
    AstMemberType<TokenAst> tok_right_parenthesis;

    TypeTupleAst(
        std::size_t pos,
        decltype(tok_left_parenthesis) &&tok_left_parenthesis,
        decltype(type_list) &&type_list,
        decltype(tok_right_parenthesis) &&tok_right_parenthesis);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;

    auto convert() -> AstMemberType<Ast>;
};
