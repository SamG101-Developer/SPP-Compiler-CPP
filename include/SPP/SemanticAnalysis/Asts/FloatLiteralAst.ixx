module;
#include <string>

export module spp.semantic_analysis.asts.float_literal_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct FloatLiteralAst;
}


struct SPP::SemanticAnalysis::Asts::FloatLiteralAst final : Ast {
    AstMemberTypeOpt<TokenAst> tok_sign;
    AstMemberType<TokenAst> integer_part;
    AstMemberType<TokenAst> tok_dot;
    AstMemberType<TokenAst> decimal_part;
    AstMemberTypeOpt<Ast> type;

    FloatLiteralAst(
        std::size_t pos,
        decltype(tok_sign) &&tok_sign,
        decltype(integer_part) &&integer_part,
        decltype(tok_dot) &&tok_dot,
        decltype(decimal_part) &&decimal_part,
        decltype(type) &&type);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
