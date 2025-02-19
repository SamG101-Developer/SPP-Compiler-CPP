module;
#include <memory>
#include <string>

export module spp.semantic_analysis.asts.type_single_ast;
import spp.compiler.compiler_stages;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.identifier_ast;
import spp.semantic_analysis.asts.generic_identifier_ast;
import spp.semantic_analysis.meta.ast_printer;


namespace SPP::SemanticAnalysis::Asts {
    export struct TypeSingleAst;
}


struct SPP::SemanticAnalysis::Asts::TypeSingleAst final : Ast, Compiler::CompilerStages {
    AstMemberType<GenericIdentifierAst> name;

    TypeSingleAst(std::size_t pos, decltype(name) &&name);
    static auto from(IdentifierAst const &identifier) -> std::unique_ptr<TypeSingleAst>;
    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
