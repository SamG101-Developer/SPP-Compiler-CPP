module;
#include <string>

export module spp.semantic_analysis.asts.type_unary_operator_namespace_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct TypeUnaryOperatorNamespaceAst;
}


struct SPP::SemanticAnalysis::Asts::TypeUnaryOperatorNamespaceAst final : Ast {
    AstMemberType<IdentifierAst> name;
    AstMemberType<TokenAst> tok_sep;

    TypeUnaryOperatorNamespaceAst(
        std::size_t pos,
        decltype(name) &&name,
        decltype(tok_sep) &&tok_sep);

    ~TypeUnaryOperatorNamespaceAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
