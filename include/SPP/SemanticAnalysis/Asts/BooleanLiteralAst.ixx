module;
#include <string>

export module spp.semantic_analysis.asts.boolean_literal_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct BooleanLiteralAst;
}


struct SPP::SemanticAnalysis::Asts::BooleanLiteralAst final : Ast {
    AstMemberType<TokenAst> val;

    BooleanLiteralAst(
        std::size_t pos,
        decltype(val) &&val);

    ~BooleanLiteralAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
