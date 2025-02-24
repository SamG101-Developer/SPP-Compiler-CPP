module;
#include <string>

export module spp.semantic_analysis.asts.generic_type_argument_unnamed_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.ast_types;


namespace SPP::SemanticAnalysis::Asts {
    export struct GenericTypeArgumentUnnamedAst;
}


struct SPP::SemanticAnalysis::Asts::GenericTypeArgumentUnnamedAst final : Ast {
    AstMemberType<Ast> type;

    GenericTypeArgumentUnnamedAst(
        std::size_t pos,
        decltype(type) &&type);

    ~GenericTypeArgumentUnnamedAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
