module;
#include <string>

export module spp.semantic_analysis.asts.let_statement_initialized_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct LetStatementInitializedAst;
}


struct SPP::SemanticAnalysis::Asts::LetStatementInitializedAst final : Ast {
    AstMemberType<TokenAst> tok_let;
    AstMemberType<Ast> variable;
    AstMemberType<TokenAst> tok_assign;
    AstMemberType<Ast> value;

    LetStatementInitializedAst(
        std::size_t pos,
        decltype(tok_let) &&tok_let,
        decltype(variable) &&variable,
        decltype(tok_assign) &&tok_assign,
        decltype(value) &&value);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
