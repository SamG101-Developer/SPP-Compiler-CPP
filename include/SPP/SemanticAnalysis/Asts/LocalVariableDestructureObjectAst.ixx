module;
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.local_variable_destructure_object_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct LocalVariableDestructureObjectAst;
}


struct SPP::SemanticAnalysis::Asts::LocalVariableDestructureObjectAst final : Ast {
    AstMemberType<TypeAst> type;
    AstMemberType<TokenAst> tok_left_parenthesis;
    AstMemberType<std::vector<LocalVariableNestedForDestructureObjectAst>> bindings;
    AstMemberType<TokenAst> tok_right_parenthesis;

    LocalVariableDestructureObjectAst(
        std::size_t pos,
        decltype(type) &&type,
        decltype(tok_left_parenthesis) &&tok_left_parenthesis,
        decltype(bindings) &&bindings,
        decltype(tok_right_parenthesis) &&tok_right_parenthesis);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
