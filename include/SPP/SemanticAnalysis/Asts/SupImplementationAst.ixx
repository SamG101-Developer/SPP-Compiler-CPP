module;
#include <memory>
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.sup_implementation_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.module_prototype_ast;
import spp.semantic_analysis.asts.token_ast;
import spp.utils.variant_intrinsics;


export namespace SPP::SemanticAnalysis::Asts {
    struct SupImplementationAst;
}


struct SPP::SemanticAnalysis::Asts::SupImplementationAst final : Ast {
    AstMemberType<TokenAst> tok_brace_l;
    AstMemberType<std::vector<SupMemberAst>> members;
    AstMemberType<TokenAst> tok_brace_r;

    SupImplementationAst(std::size_t pos, decltype(tok_brace_l) &&tok_brace_l, decltype(members) &&members, decltype(tok_brace_r) &&tok_brace_r);
    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
