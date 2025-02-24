module;
#include <memory>
#include <optional>
#include <string>

export module spp.semantic_analysis.asts.gen_expression_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct GenExpressionAst;
}


struct SPP::SemanticAnalysis::Asts::GenExpressionAst final : Ast {
    AstMemberType<TokenAst> tok_gen;
    AstMemberTypeOpt<TokenAst> tok_with;
    AstMemberType<ConventionAst> conv;
    AstMemberTypeOpt<Ast> expr;

    std::optional<Ast*> _cor_ret_type;

    GenExpressionAst(
        std::size_t pos,
        decltype(tok_gen) &&tok_gen,
        decltype(tok_with) &&tok_with,
        decltype(conv) &&conv,
        decltype(expr) &&expr);

    ~GenExpressionAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
