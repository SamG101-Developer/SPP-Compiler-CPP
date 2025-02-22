module;
#include <string>

export module spp.semantic_analysis.asts.type_postfix_operator_nested_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct TypePostfixOperatorNestedAst;
}


struct SPP::SemanticAnalysis::Asts::TypePostfixOperatorNestedAst final : Ast {
    AstMemberType<TokenAst> tok_sep;
    AstMemberType<TypeSingleAst> name;

    TypePostfixOperatorNestedAst(
        std::size_t pos,
        decltype(tok_sep) &&tok_sep,
        decltype(name) &&name);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
