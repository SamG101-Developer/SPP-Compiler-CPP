module;
#include <string>

export module spp.semantic_analysis.asts.generic_comp_parameter_required_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct GenericCompParameterRequiredAst;
}


struct SPP::SemanticAnalysis::Asts::GenericCompParameterRequiredAst final : Ast {
    AstMemberType<TokenAst> tok_cmp;
    AstMemberType<Ast> name;
    AstMemberType<TokenAst> tok_colon;
    AstMemberType<Ast> type;

    GenericCompParameterRequiredAst(
        std::size_t pos,
        decltype(tok_cmp) &&tok_cmp,
        decltype(name) &&name,
        decltype(tok_colon) &&tok_colon,
        decltype(type) &&type);

    ~GenericCompParameterRequiredAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
