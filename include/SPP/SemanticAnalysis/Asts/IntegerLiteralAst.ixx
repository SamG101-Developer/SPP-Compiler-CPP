module;
#include <string>

export module spp.semantic_analysis.asts.integer_literal_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct IntegerLiteralAst;
}


struct SPP::SemanticAnalysis::Asts::IntegerLiteralAst final : Ast {
    AstMemberTypeOpt<TokenAst> tok_sign;
    AstMemberType<TokenAst> val;
    AstMemberTypeOpt<Ast> type;

    IntegerLiteralAst(
        std::size_t pos,
        decltype(tok_sign) &&tok_sign,
        decltype(val) &&val,
        decltype(type) &&type);

    ~IntegerLiteralAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
