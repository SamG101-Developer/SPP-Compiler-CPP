module;
#include <string>

export module spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Meta {
    class AstPrinter;
}


class SPP::SemanticAnalysis::Meta::AstPrinter {
    std::uint32_t indent_size = 4;
    std::uint32_t indent_level = 0;

    auto increase_indent() -> void;
    auto decrease_indent() -> void;
    auto format_code(std::string &&code) const -> std::string;

public:
    explicit AstPrinter(std::uint32_t indent_size = 4);
    template <typename T>
    auto print(AstPrinter &printer, std::string &&code) -> std::string;
};
