module;
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.class_prototype_ast;
import spp.compiler.compiler_stages;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.annotation_ast;
import spp.semantic_analysis.asts.class_implementation_ast;
import spp.semantic_analysis.asts.generic_parameter_group_ast;
import spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.asts.type_single_ast;
import spp.semantic_analysis.asts.where_block_ast;
import spp.semantic_analysis.meta.ast_printer;


namespace SPP::SemanticAnalysis::Asts {
    export struct ClassPrototypeAst;
}


struct SPP::SemanticAnalysis::Asts::ClassPrototypeAst final : Ast, Compiler::CompilerStages {
    AstMemberType<std::vector<AnnotationAst>> annotations;
    AstMemberType<TokenAst> tok_cls;
    AstMemberType<TypeSingleAst> name;
    AstMemberTypeOpt<GenericParameterGroupAst> generic_params;
    AstMemberTypeOpt<WhereBlockAst> where_block;
    AstMemberType<ClassImplementationAst> class_impl;

    bool is_alias = false;

    ClassPrototypeAst(std::size_t pos, decltype(annotations) &&annotations, decltype(tok_cls) &&tok_cls, decltype(name) &&name, decltype(generic_params) &&generic_args, decltype(where_block) &&where_block, decltype(class_impl) &&class_impl);
    auto print(Meta::AstPrinter &printer) const -> std::string override;
};
