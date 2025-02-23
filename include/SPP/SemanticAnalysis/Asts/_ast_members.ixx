module;
#include <memory>
#include <optional>
#include <vector>

export module spp.semantic_analysis.asts.ast_members;


template <typename T>
struct ast_member {
    using type = std::unique_ptr<T>;
};


template <typename T>
struct ast_member<std::vector<T>> {
    using type = std::vector<std::unique_ptr<T>>;
};


namespace SPP::SemanticAnalysis::Asts {
    export template <typename T>
    using AstMemberType = typename ast_member<T>::type;

    export template <typename T>
    using AstMemberTypeOpt = std::optional<AstMemberType<T>>;
}
