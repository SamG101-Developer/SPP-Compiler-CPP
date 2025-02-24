module;
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.global_constant_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct GlobalConstantAst;
}


struct SPP::SemanticAnalysis::Asts::GlobalConstantAst final : Ast {
    AstMemberType<std::vector<AnnotationAst>> annotations;
    AstMemberType<TokenAst> tok_cmp;
    AstMemberType<IdentifierAst> name;
    AstMemberType<TokenAst> tok_colon;
    AstMemberType<Ast> type;
    AstMemberType<TokenAst> tok_assign;
    AstMemberType<Ast> value;

    GlobalConstantAst(
        std::size_t pos,
        decltype(annotations) &&annotations,
        decltype(tok_cmp) &&tok_cmp,
        decltype(name) &&name,
        decltype(tok_colon) &&tok_colon,
        decltype(type) &&type,
        decltype(tok_assign) &&tok_assign,
        decltype(value) &&value);

    ~GlobalConstantAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
