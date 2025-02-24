module;
#include <string>

export module spp.semantic_analysis.asts.type_postfix_operator_nested_type_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct TypePostfixOperatorNestedTypeAst;
}


struct SPP::SemanticAnalysis::Asts::TypePostfixOperatorNestedTypeAst final : Ast {
    AstMemberType<TokenAst> tok_sep;
    AstMemberType<TypeSingleAst> name;

    TypePostfixOperatorNestedTypeAst(
        std::size_t pos,
        decltype(tok_sep) &&tok_sep,
        decltype(name) &&name);

    ~TypePostfixOperatorNestedTypeAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
