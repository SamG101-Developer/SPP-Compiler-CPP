module;
#include <memory>
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.class_implementation_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.token_ast;


export namespace SPP::SemanticAnalysis::Asts {
    struct ClassImplementationAst;
}


struct SPP::SemanticAnalysis::Asts::ClassImplementationAst final : Ast {
    AstMemberType<TokenAst> tok_brace_l;
    AstMemberType<std::vector<Ast>> members;
    AstMemberType<TokenAst> tok_brace_r;

    ClassImplementationAst(
        std::size_t pos,
        decltype(tok_brace_l) &&tok_brace_l,
        decltype(members) &&members,
        decltype(tok_brace_r) &&tok_brace_r);

    ~ClassImplementationAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
