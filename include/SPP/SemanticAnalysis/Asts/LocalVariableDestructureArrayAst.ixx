module;
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.local_variable_destructure_array_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct LocalVariableDestructureArrayAst;
}


struct SPP::SemanticAnalysis::Asts::LocalVariableDestructureArrayAst final : Ast {
    AstMemberType<TokenAst> tok_left_bracket;
    AstMemberType<std::vector<Ast>> bindings;
    AstMemberType<TokenAst> tok_right_bracket;

    LocalVariableDestructureArrayAst(
        std::size_t pos,
        decltype(tok_left_bracket) &&tok_left_bracket,
        decltype(bindings) &&bindings,
        decltype(tok_right_bracket) &&tok_right_bracket);

    ~LocalVariableDestructureArrayAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
