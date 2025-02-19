module;
#include <memory>
#include <string>

export module spp.semantic_analysis.scoping.symbol;
import spp.utils.converter;


namespace SPP::SemanticAnalysis::Asts {
    struct IdentifierAst;
}


namespace SPP::SemanticAnalysis::Scoping {
    export struct Symbol;
    export struct AliasSymbol;
    export struct NamespaceSymbol;
    export struct TypeSymbol;
    export struct VariableSymbol;
    struct Scope;
}


struct SPP::SemanticAnalysis::Scoping::Symbol : Utils::JsonConverter, Utils::StringConverter {
    ~Symbol() override = default;
};


struct SPP::SemanticAnalysis::Scoping::NamespaceSymbol final : Symbol {
    std::unique_ptr<Asts::IdentifierAst> identifier;
    Scope *scope = nullptr;

    NamespaceSymbol(NamespaceSymbol &) = delete;
    NamespaceSymbol(NamespaceSymbol &&) noexcept = default;
    auto operator=(NamespaceSymbol &) -> NamespaceSymbol& = delete;
    auto operator=(NamespaceSymbol &&) noexcept -> NamespaceSymbol& = default;

    auto copy() const -> NamespaceSymbol;
    auto to_json() const -> std::string override;
    auto to_string() const -> std::string override;
};
