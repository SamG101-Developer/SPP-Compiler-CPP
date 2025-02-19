module;
#include <memory>
#include <optional>
#include <variant>
#include <vector>

export module spp.semantic_analysis.asts.ast_members;
import spp.utils.variant_intrinsics;


template <typename T>
struct ast_member {
    using type = std::unique_ptr<T>;
};


template <typename... Ts>
struct ast_member<std::variant<Ts...>> {
    using type = SPP::Utils::UniqueVariant<std::variant<Ts...>>;
};


template <typename T>
struct ast_member<std::vector<T>> {
    using type = std::vector<std::unique_ptr<T>>;
};


template <typename... Ts>
struct ast_member<std::vector<std::variant<Ts...>>> {
    using type = std::vector<SPP::Utils::UniqueVariant<std::variant<Ts...>>>;
};


namespace SPP::SemanticAnalysis::Asts {
    export template <typename T>
    using AstMemberType = typename ast_member<T>::type;

    export template <typename T>
    using AstMemberTypeOpt = std::optional<AstMemberType<T>>;
}
