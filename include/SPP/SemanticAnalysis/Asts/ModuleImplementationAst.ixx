module;
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.module_implementation_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


namespace SPP::SemanticAnalysis::Asts {
    export struct ModuleImplementationAst;
}


struct SPP::SemanticAnalysis::Asts::ModuleImplementationAst final : Ast {
    std::vector<AstMemberType<Ast>> members;

    ModuleImplementationAst(
        std::size_t pos,
        decltype(members) &&members);

    ~ModuleImplementationAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
