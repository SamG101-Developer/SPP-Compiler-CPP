module;
#include <string>

export module spp.semantic_analysis.asts.generic_type_parameter_required_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct GenericTypeParameterRequiredAst;
}


struct SPP::SemanticAnalysis::Asts::GenericTypeParameterRequiredAst final : Ast {
    AstMemberType<TypeAst> name;
    AstMemberTypeOpt<GenericTypeParameterInlineConstraintsAst> constraints;

    GenericTypeParameterRequiredAst(
        std::size_t pos,
        decltype(name) &&name,
        decltype(constraints) &&constraints);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
