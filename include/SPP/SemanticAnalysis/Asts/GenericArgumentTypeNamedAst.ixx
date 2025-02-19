module;
#include <string>

export module spp.semantic_analysis.asts.generic_argument_type_named_ast;
import spp.compiler.compiler_stages;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.ast_types;

namespace SPP::SemanticAnalysis::Asts {
    export struct GenericArgumentTypeNamedAst;
}


struct SPP::SemanticAnalysis::Asts::GenericArgumentTypeNamedAst final : Ast, Compiler::CompilerStages {
    AstMemberType<TypeAst> name;
    AstMemberType<TokenAst> tok_assign;
    AstMemberType<TypeAst> type;

    GenericArgumentTypeNamedAst(std::size_t pos, decltype(type) &&type, decltype(tok_assign) &&tok_assign, decltype(name) &&name);
    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
