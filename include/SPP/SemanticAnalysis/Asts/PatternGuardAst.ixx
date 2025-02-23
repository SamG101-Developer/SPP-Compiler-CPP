module;
#include <string>

export module spp.semantic_analysis.asts.pattern_guard_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct PatternGuardAst;
}


struct SPP::SemanticAnalysis::Asts::PatternGuardAst final : Ast {
    AstMemberType<TokenAst> tok_guard;
    AstMemberType<Ast> expr;

    PatternGuardAst(
        std::size_t pos,
        decltype(tok_guard) &&tok_guard,
        decltype(expr) &&expr);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
