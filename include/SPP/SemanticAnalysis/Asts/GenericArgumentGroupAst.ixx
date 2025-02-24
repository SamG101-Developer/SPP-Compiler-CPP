module;
#include <memory>
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.generic_argument_group_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.ast_types;


namespace SPP::SemanticAnalysis::Asts {
    export struct GenericArgumentGroupAst;
}


struct SPP::SemanticAnalysis::Asts::GenericArgumentGroupAst final : Ast {
    AstMemberType<TokenAst> tok_paren_l;
    AstMemberType<std::vector<Ast>> members;
    AstMemberType<TokenAst> tok_paren_r;

    GenericArgumentGroupAst(
        std::size_t pos,
        decltype(tok_paren_l) &&tok_paren_l,
        decltype(members) &&members,
        decltype(tok_paren_r) &&tok_paren_r);

    static auto from_empty() -> std::unique_ptr<GenericArgumentGroupAst>;

    ~GenericArgumentGroupAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
