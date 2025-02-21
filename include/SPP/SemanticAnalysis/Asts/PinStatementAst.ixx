module;
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.pin_statement_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct PinStatementAst;
}


struct SPP::SemanticAnalysis::Asts::PinStatementAst final : Ast {
    AstMemberType<TokenAst> tok_pin;
    AstMemberType<std::vector<ExpressionAst>> pins;

    PinStatementAst(
        std::size_t pos,
        decltype(tok_pin) &&tok_pin,
        decltype(pins) &&pins);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
