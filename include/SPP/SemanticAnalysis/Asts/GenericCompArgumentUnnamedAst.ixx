module;
#include <string>

export module spp.semantic_analysis.asts.generic_comp_argument_unnamed_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct GenericCompArgumentUnnamedAst;
}


struct SPP::SemanticAnalysis::Asts::GenericCompArgumentUnnamedAst final : Ast {
    AstMemberType<Ast> value;

    GenericCompArgumentUnnamedAst(
        std::size_t pos,
        decltype(value) &&value);

    ~GenericCompArgumentUnnamedAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
