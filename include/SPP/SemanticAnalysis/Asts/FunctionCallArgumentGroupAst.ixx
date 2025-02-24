module;
#include <memory>
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.function_call_argument_group_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.token_ast;


export namespace SPP::SemanticAnalysis::Asts {
    struct FunctionCallArgumentGroupAst;
}


struct SPP::SemanticAnalysis::Asts::FunctionCallArgumentGroupAst final : Ast {
    AstMemberType<TokenAst> tok_paren_l;
    AstMemberType<std::vector<Ast>> members;
    AstMemberType<TokenAst> tok_paren_r;

    FunctionCallArgumentGroupAst(
        std::size_t pos,
        decltype(tok_paren_l) &&tok_paren_l,
        decltype(members) &&members,
        decltype(tok_paren_r) &&tok_paren_r);

    ~FunctionCallArgumentGroupAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
