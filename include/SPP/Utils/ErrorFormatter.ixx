module;
#include <vector>
#include <string>


export module spp.utils.error_formatter;
import spp.lexical_analysis.tokens;

export namespace SPP::Utils {
    class ErrorFormatter;
}


class SPP::Utils::ErrorFormatter {
    std::vector<LexicalAnalysis::RawToken> token_stream;
    std::string file_path;

public:
    ErrorFormatter(std::vector<LexicalAnalysis::RawToken> token_stream, std::string file_path);
    auto error(std::size_t start_pos, std::string &&message = "", std::string &&tag_message = "", bool minimal = false) -> std::string;
};
