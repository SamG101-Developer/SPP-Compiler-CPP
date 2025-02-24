module;
#include <memory>
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.generic_parameter_group_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.ast_types;


namespace SPP::SemanticAnalysis::Asts {
    export struct GenericParameterGroupAst;
}


struct SPP::SemanticAnalysis::Asts::GenericParameterGroupAst final : Ast {
    AstMemberType<TokenAst> tok_left_parenthesis;
    AstMemberType<std::vector<Ast>> generic_args_groups;
    AstMemberType<TokenAst> tok_right_parenthesis;

    GenericParameterGroupAst(
        std::size_t pos,
        decltype(tok_left_parenthesis) &&tok_left_parenthesis,
        decltype(generic_args_groups) &&generic_args_groups,
        decltype(tok_right_parenthesis) &&tok_right_parenthesis);

    static auto from_empty() -> std::unique_ptr<GenericParameterGroupAst>;

    ~GenericParameterGroupAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
