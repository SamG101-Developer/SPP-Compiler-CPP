module;
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.object_initializer_argument_group_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct ObjectInitializerArgumentGroupAst;
}


struct SPP::SemanticAnalysis::Asts::ObjectInitializerArgumentGroupAst final : Ast {
    AstMemberType<TokenAst> tok_left_parenthesis;
    AstMemberType<std::vector<Ast>> obj_args_group;
    AstMemberType<TokenAst> tok_right_parenthesis;

    ObjectInitializerArgumentGroupAst(
        std::size_t pos,
        decltype(tok_left_parenthesis) &&tok_left_parenthesis,
        decltype(obj_args_group) &&obj_args_group,
        decltype(tok_right_parenthesis) &&tok_right_parenthesis);

    ~ObjectInitializerArgumentGroupAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
