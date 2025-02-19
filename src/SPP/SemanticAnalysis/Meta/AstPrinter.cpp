module;
#include <re2/re2.h>

module spp.semantic_analysis.meta.ast_printer;


SPP::SemanticAnalysis::Meta::AstPrinter::AstPrinter(const std::uint32_t indent_size)
    : indent_size(indent_size) {
}


auto SPP::SemanticAnalysis::Meta::AstPrinter::increase_indent() -> void {
    indent_level += indent_size;
}


auto SPP::SemanticAnalysis::Meta::AstPrinter::decrease_indent() -> void {
    indent_level -= indent_size;
}


auto SPP::SemanticAnalysis::Meta::AstPrinter::format_code(std::string&& code) const -> std::string {
    // Python code: return re.sub(r"\n", "\n" + " " * self._current_indent, code)
    auto formatted_string = std::string(code);
    RE2::Replace(&formatted_string, RE2("\n"), "\n" + std::string(indent_level, ' '));
    return formatted_string;
}


template <typename T>
auto SPP::SemanticAnalysis::Meta::AstPrinter::print(AstPrinter& printer, std::string &&code) -> std::string {
    const auto indent = false;  // std::is_same_v<T, InnerScopeAst> || std::is_same_v<T, ClassImeplementationAst> || std::is_same_v<T, SupImplementationAst> || std::is_same_v<T, FunctionImplementationAst>;
    auto formatted_code = std::string();

    if (indent) {
        printer.increase_indent();
        formatted_code = printer.format_code(std::move(code));
        printer.decrease_indent();
    }
    else {
        formatted_code = printer.format_code(std::move(code));
    }

    return formatted_code;
}



