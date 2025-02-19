module;
#include <string>

export module spp.semantic_analysis.asts.coroutine_prototype_ast;
import spp.semantic_analysis.asts.function_prototype_ast;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct CoroutinePrototypeAst;
}


struct SPP::SemanticAnalysis::Asts::CoroutinePrototypeAst final : FunctionPrototypeAst {
    using FunctionPrototypeAst::FunctionPrototypeAst;
    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
