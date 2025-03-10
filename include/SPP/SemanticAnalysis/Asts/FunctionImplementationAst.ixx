module;
#include <memory>
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.function_implementation_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.module_prototype_ast;
import spp.semantic_analysis.asts.token_ast;


export namespace SPP::SemanticAnalysis::Asts {
    struct FunctionImplementationAst;
}


struct SPP::SemanticAnalysis::Asts::FunctionImplementationAst final : Ast {
    AstMemberType<TokenAst> tok_brace_l;
    AstMemberType<std::vector<Ast>> members;
    AstMemberType<TokenAst> tok_brace_r;

    FunctionImplementationAst(
        std::size_t pos,
        decltype(tok_brace_l) &&tok_brace_l,
        decltype(members) &&members,
        decltype(tok_brace_r) &&tok_brace_r);

    ~FunctionImplementationAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
