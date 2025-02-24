module;
#include <memory>
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.sup_implementation_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.ast_types;


export namespace SPP::SemanticAnalysis::Asts {
    struct SupImplementationAst;
}


struct SPP::SemanticAnalysis::Asts::SupImplementationAst final : Ast {
    AstMemberType<TokenAst> tok_brace_l;
    AstMemberType<std::vector<Ast>> members;
    AstMemberType<TokenAst> tok_brace_r;

    SupImplementationAst(
        std::size_t pos,
        decltype(tok_brace_l) &&tok_brace_l,
        decltype(members) &&members,
        decltype(tok_brace_r) &&tok_brace_r);

    ~SupImplementationAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
