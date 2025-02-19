module;
#include <any>
#include <map>
#include <memory>
#include <string>

export module spp.semantic_analysis.mixins.type_infer;
import spp.semantic_analysis.scoping.scope_manager;
import spp.semantic_analysis.scoping.scope;
import spp.utils.converter;


// namespace SPP::SemanticAnalysis::Scoping {
//     class Scope;
//     class ScopeManager;
// }


namespace SPP::SemanticAnalysis::Asts {
    struct ConventionAst;
    struct TypeSingleAst;
}


export namespace SPP::SemanticAnalysis::Mixins {
    struct InferredType;
    struct TypeInfer;
}


struct SPP::SemanticAnalysis::Mixins::InferredType final : Utils::StringConverter {
    std::unique_ptr<Asts::ConventionAst> convention;
    std::unique_ptr<Asts::TypeSingleAst> type;

    explicit InferredType(Asts::TypeSingleAst &&type, Asts::ConventionAst convention);
    ~InferredType() override;

    auto from_type(Asts::TypeSingleAst &&type);
    auto eq(InferredType const *that, Scoping::Scope const *this_scope, Scoping::Scope const *that_scope = nullptr) const -> bool;
    auto strip() -> InferredType;
    auto to_string() const -> std::string override;
};


struct SPP::SemanticAnalysis::Mixins::TypeInfer {
    virtual ~TypeInfer() = default;
    virtual auto infer_type(Scoping::ScopeManager *scope_manager, std::map<std::string, std::any> &meta) -> InferredType = 0;
};
