module;
#include <string>

export module spp.semantic_analysis.asts.let_statement_uninitialized_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct LetStatementUninitializedAst;
}


struct SPP::SemanticAnalysis::Asts::LetStatementUninitializedAst final : Ast {
    AstMemberType<TokenAst> tok_let;
    AstMemberType<Ast> variable;
    AstMemberType<TokenAst> tok_colon;
    AstMemberType<ConventionAst> conv;
    AstMemberType<Ast> type;

    LetStatementUninitializedAst(
        std::size_t pos,
        decltype(tok_let) &&tok_let,
        decltype(variable) &&variable,
        decltype(tok_colon) &&tok_colon,
        decltype(conv) &&conv,
        decltype(type) &&type);

    ~LetStatementUninitializedAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
