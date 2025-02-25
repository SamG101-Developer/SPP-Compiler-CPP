module;
#include <memory>
#include <string>

export module spp.semantic_analysis.asts.generic_identifier_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.ast_types;


namespace SPP::SemanticAnalysis::Asts {
    export struct GenericIdentifierAst;
}


struct SPP::SemanticAnalysis::Asts::GenericIdentifierAst final : Ast {
    std::string value;
    AstMemberType<GenericArgumentGroupAst> generic_args_group;

    GenericIdentifierAst(
        std::size_t pos,
        decltype(value) &&value,
        decltype(generic_args_group) &&generic_args_group);

    static auto from(IdentifierAst const &identifier) -> std::unique_ptr<GenericIdentifierAst>;

    static auto from(TypeSingleAst const &identifier) -> std::unique_ptr<GenericIdentifierAst>;

    static auto from(GenericIdentifierAst const &identifier) -> std::unique_ptr<GenericIdentifierAst>;

    static auto empty() -> std::unique_ptr<GenericIdentifierAst>;

    ~GenericIdentifierAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
