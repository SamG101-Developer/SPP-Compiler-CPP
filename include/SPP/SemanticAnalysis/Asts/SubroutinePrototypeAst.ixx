module;
#include <string>

export module spp.semantic_analysis.asts.subroutine_prototype_ast;
import spp.semantic_analysis.asts.function_prototype_ast;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct SubroutinePrototypeAst;
}


struct SPP::SemanticAnalysis::Asts::SubroutinePrototypeAst final : FunctionPrototypeAst {
    using FunctionPrototypeAst::FunctionPrototypeAst;
    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
