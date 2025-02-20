module;
#include <memory>
#include <string>

export module spp.semantic_analysis.asts.module_prototype_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.module_implementation_ast;
import spp.semantic_analysis.meta.ast_printer;


namespace SPP::SemanticAnalysis::Asts {
    export struct ModulePrototypeAst;
}


struct SPP::SemanticAnalysis::Asts::ModulePrototypeAst final : Ast {
    AstMemberType<ModuleImplementationAst> body;
    std::string name = "";

    ModulePrototypeAst(std::size_t pos, decltype(body) &&body);
    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
