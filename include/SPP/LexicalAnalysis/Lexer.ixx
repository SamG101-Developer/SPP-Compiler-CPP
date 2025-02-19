module;
#include <string_view>
#include <vector>

export module spp.lexical_analysis.lexer;
import spp.lexical_analysis.tokens;

namespace SPP::LexicalAnalysis {
    export class Lexer;
}


class SPP::LexicalAnalysis::Lexer {
    std::string_view code;

public:
    explicit Lexer(std::string_view code);
    [[nodiscard]] auto Lex() const -> std::vector<RawToken>;
};
