module;
#include <string>

export module spp.semantic_analysis.asts.generic_type_parameter_variadic_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct GenericTypeParameterVariadicAst;
}


struct SPP::SemanticAnalysis::Asts::GenericTypeParameterVariadicAst final : Ast {
    AstMemberType<TokenAst> tok_variadic;
    AstMemberType<Ast> name;
    AstMemberTypeOpt<GenericTypeParameterInlineConstraintsAst> constraints;

    GenericTypeParameterVariadicAst(
        std::size_t pos,
        decltype(tok_variadic) &&tok_variadic,
        decltype(name) &&name,
        decltype(constraints) &&constraints);

    ~GenericTypeParameterVariadicAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
