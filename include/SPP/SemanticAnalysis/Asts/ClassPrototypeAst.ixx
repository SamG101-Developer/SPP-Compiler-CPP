module;
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.class_prototype_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.ast_types;


namespace SPP::SemanticAnalysis::Asts {
    export struct ClassPrototypeAst;
}


struct SPP::SemanticAnalysis::Asts::ClassPrototypeAst final : Ast {
    AstMemberType<std::vector<AnnotationAst>> annotations;
    AstMemberType<TokenAst> tok_cls;
    AstMemberType<TypeSingleAst> name;
    AstMemberType<GenericParameterGroupAst> generic_params;
    AstMemberType<WhereBlockAst> where_block;
    AstMemberType<ClassImplementationAst> class_impl;

    bool is_alias = false;

    ClassPrototypeAst(
        std::size_t pos,
        decltype(annotations) &&annotations,
        decltype(tok_cls) &&tok_cls,
        decltype(name) &&name,
        decltype(generic_params) &&generic_args,
        decltype(where_block) &&where_block,
        decltype(class_impl) &&class_impl);

    ~ClassPrototypeAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
