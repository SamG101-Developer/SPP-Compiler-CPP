module;
#include <string>

export module spp.semantic_analysis.asts.generic_type_parameter_optional_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct GenericTypeParameterOptionalAst;
}


struct SPP::SemanticAnalysis::Asts::GenericTypeParameterOptionalAst final : Ast {
    AstMemberType<Ast> name;
    AstMemberTypeOpt<GenericTypeParameterInlineConstraintsAst> constraints;
    AstMemberType<TokenAst> tok_assign;
    AstMemberType<Ast> default_type;

    GenericTypeParameterOptionalAst(
        std::size_t pos,
        decltype(name) &&name,
        decltype(constraints) &&constraints,
        decltype(tok_assign) &&tok_assign,
        decltype(default_type) &&default_type);

    ~GenericTypeParameterOptionalAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
