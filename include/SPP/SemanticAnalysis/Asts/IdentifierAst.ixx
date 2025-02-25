module;
#include <string>

export module spp.semantic_analysis.asts.identifier_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.mixins.type_infer;
import spp.semantic_analysis.scoping.scope_manager;


namespace SPP::SemanticAnalysis::Asts {
    export struct IdentifierAst;
}


struct SPP::SemanticAnalysis::Asts::IdentifierAst final : Ast {
    std::string value;

    IdentifierAst(
        std::size_t pos,
        decltype(value) &&value);

    ~IdentifierAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
