module;
#include <string>

export module spp.semantic_analysis.asts.string_literal_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct StringLiteralAst;
}


struct SPP::SemanticAnalysis::Asts::StringLiteralAst final : Ast {
    AstMemberType<TokenAst> val;

    StringLiteralAst(
        std::size_t pos,
        decltype(val) &&val);

    ~StringLiteralAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
