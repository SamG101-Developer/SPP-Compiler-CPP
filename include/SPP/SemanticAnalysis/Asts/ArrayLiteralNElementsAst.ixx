module;
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.array_literal_n_elements_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct ArrayLiteralNElementsAst;
}


struct SPP::SemanticAnalysis::Asts::ArrayLiteralNElementsAst final : Ast {
    AstMemberType<TokenAst> tok_left_bracket;
    AstMemberType<std::vector<Ast>> elements;
    AstMemberType<TokenAst> tok_right_bracket;

    ArrayLiteralNElementsAst(
        std::size_t pos,
        decltype(tok_left_bracket) &&tok_left_bracket,
        decltype(elements) &&elements,
        decltype(tok_right_bracket) &&tok_right_bracket);

    ~ArrayLiteralNElementsAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
