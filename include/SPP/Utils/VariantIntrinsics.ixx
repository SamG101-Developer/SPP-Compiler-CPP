module;
#include <memory>
#include <variant>


export module spp.utils.variant_intrinsics;


template <typename... Types>
struct combine_variants;

// 2+ types
template <typename L, typename R, typename... Rest>
struct combine_variants<L, R, Rest...> {
    using type = typename combine_variants<typename combine_variants<L, R>::type, Rest...>::type;
};

// std::variant followed by variant type
template <typename... TypesL, typename... TypesR>
struct combine_variants<std::variant<TypesL...>, std::variant<TypesR...>> {
    using type = std::variant<TypesL..., TypesR...>;
};

// std::variant followed by 1 non-variant type
template <typename... TypesL, typename R>
struct combine_variants<std::variant<TypesL...>, R> {
    using type = std::variant<TypesL..., R>;
};

// 1 non-variant type followed by std::variant
template <typename L, typename... TypesR>
struct combine_variants<L, std::variant<TypesR...>> {
    using type = std::variant<L, TypesR...>;
};

// 2 non-variant types
template <typename L, typename R>
struct combine_variants<L, R> {
    using type = std::variant<L, R>;
};

// 1 non-variant type
template <typename T>
struct combine_variants<T> {
    using type = std::variant<T>;
};

// 0 types
template <>
struct combine_variants<> {
    using type = std::variant<>;
};


// Convert std::variant<int, bool> to std::variant<std::unique_ptr<int>, std::unique_ptr<bool>>
template <typename... Types>
struct unique_variant;

template <typename... Types>
struct unique_variant<std::variant<Types...>> {
    using type = std::variant<std::unique_ptr<Types>...>;
};


namespace SPP::Utils {
    /**
     * The CollapsibleVariant is a variant, which can take any amount of type arguments. It produces a std::variant,
     * which collapses all other std::variant's type arguments into itself, and adds any other non-std::variant type
     * arguments. For example, CollapsibleVariant<std::variant<int, bool>, std::variant<std::string, std::vector<int>>,
     * double> will produce std::variant<int, bool, std::string, std::vector<int>, double>.
     */
    export template <typename... Types>
    using CollapsingVariant = typename combine_variants<Types...>::type;

    /**
     * The UniqueVariant<Types...> is a variant that converts the Types into std::unique_ptr<Types> before storing them.
     * For example, declaring a std::UniqueVariant<int, std::string> object is the same as declaring a
     * std::variant<std::unique_ptr<int>, std::unique_ptr<std::string>> object.
     */
    export template <typename T>
    using UniqueVariant = typename unique_variant<T>::type;

    /**
     * Convert a variant type into another variant type. This allows for something like std::variant<A, B> ->
     * std::variant<A, B, C> easily. The new variant type arguments must be a superset of the old variant type
     * arguments.
     */
    export template <typename Out, typename In>
    auto convert_variant(In&& variant) -> Out {
        return std::visit([](auto&& arg) -> Out {
            return arg;
        }, std::forward<In>(variant));
    }
}
