module;
#include <string>

export module spp.semantic_analysis.asts.object_initializer_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct ObjectInitializerAst;
}


struct SPP::SemanticAnalysis::Asts::ObjectInitializerAst final : Ast {
    AstMemberType<Ast> type;
    AstMemberType<ObjectInitializerArgumentGroupAst> obj_args_group;

    ObjectInitializerAst(
        std::size_t pos,
        decltype(type) &&type,
        decltype(obj_args_group) &&obj_args_group);

    ~ObjectInitializerAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};
