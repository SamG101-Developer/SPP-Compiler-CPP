module;
#include <memory>
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.module_implementation_ast;
import spp.compiler.compiler_stages;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;
import spp.utils.variant_intrinsics;


namespace SPP::SemanticAnalysis::Asts {
    export struct ModuleImplementationAst;
}


struct SPP::SemanticAnalysis::Asts::ModuleImplementationAst final : Ast, Compiler::CompilerStages {
    std::vector<AstMemberType<ModuleMemberAst>> members;

    ModuleImplementationAst(std::size_t pos, decltype(members) &&members);
    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
