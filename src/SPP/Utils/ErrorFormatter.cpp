module;
#include <string>


module spp.utils.error_formatter;
import spp.lexical_analysis.tokens;
import spp.utils.pretty_printer;

import genex.operations.push_back;
import genex.algorithms.contains;
import genex.algorithms.count;
import genex.algorithms.find;
import genex.views.enumerate;
import genex.views.map;
import genex.views.join;
import genex.views.take;
import genex.views.drop;
import genex.views.slice;
import genex.views.reverse;
import genex.numeric.accumulate;
import genex.range.conversion;
import genex.views.to;
import genex.generator;


SPP::Utils::ErrorFormatter::ErrorFormatter(std::vector<LexicalAnalysis::RawToken> token_stream, std::string file_path)
    : token_stream(std::move(token_stream)), file_path(std::move(file_path)) {
}


auto SPP::Utils::ErrorFormatter::error(std::size_t start_pos, std::string &&message, std::string&& tag_message, const bool minimal) -> std::string {
    using namespace PrettyPrinter;
    using namespace LexicalAnalysis;

    while (genex::algorithms::contains(TokenTypesSpecial::skippable_tokens(), token_stream[start_pos].tok_type)) {
        start_pos++;
    }

    // Get the tokens at the start and end of the line containing the error. Skip the leading newline.
    auto is_newline_tok = [](const std::pair<size_t, RawToken> &tok) { return tok.second.tok_type == RawTokenTypes::TkNewLine; };
    auto [err_line_spos, _1] = *genex::algorithms::find_if(token_stream | genex::views::take(start_pos) | genex::views::enumerate | genex::views::reverse, is_newline_tok);
    auto [err_line_epos, _2] = *genex::algorithms::find_if(token_stream | genex::views::drop(start_pos) | genex::views::enumerate, is_newline_tok);
    auto err_line_toks = token_stream | ranges::views::slice(err_line_spos, err_line_epos);
    auto err_line_as_string = err_line_toks | genex::views::map(&RawToken::tok_metadata) | ranges::views::join | genex::views::to<std::string>;

    // Get the line number of the error.
    const auto err_line_num = std::to_string(genex::algorithms::count(token_stream | genex::views::take(start_pos), RawTokenTypes::TkNewLine, &RawToken::tok_type));

    // The number of "^" is the length of the token data where the error is.
    auto carets = std::string(token_stream[start_pos].tok_metadata.size(), '^');
    carets.insert(0, genex::algorithms::accumulate(token_stream | genex::views::slice(err_line_spos, start_pos) | genex::views::map(&RawToken::tok_size), 0), ' ');

    // Print the preceding spaces before the error line
    const auto l1 = err_line_as_string.size();
    while (err_line_as_string.find("  ") != std::string::npos) { err_line_as_string.replace(err_line_as_string.find("  "), 2, ""); }
    carets |= genex::actions::slice(static_cast<std::size_t>(0), l1 - err_line_as_string.size());
    carets += Foreground::LightWhiteEx + Style::Bold + "<-" + tag_message;

    // Padding
    const auto left_padding = std::string(err_line_num.size(), ' ');
    constexpr auto bar_character = '|';

    if (minimal) {
        return Foreground::LightWhiteEx + Style::Bold
            + "Error in file " + file_path + ", on line " + err_line_num + ":\n"
            + Foreground::LightWhiteEx + left_padding + " " + bar_character + " "
            + Foreground::LightGreenEx + err_line_num + " " + bar_character + " " + err_line_as_string + "\n"
            + Foreground::LightWhiteEx + left_padding + " " + bar_character + " " + carets + Style::Normal + Foreground::Green + " " + carets + "\n";
    }
    return Foreground::LightWhiteEx + Style::Bold
        + "Context from file " + file_path + ", on line " + err_line_num + ":\n"
        + Foreground::LightWhiteEx + left_padding + " " + bar_character + " "
        + Foreground::LightRedEx + err_line_num + " " + bar_character + " " + err_line_as_string + "\n"
        + Foreground::LightWhiteEx + left_padding + " " + bar_character + " " + carets + Style::Normal + Foreground::Red + " " + carets + "\n"
        + Style::Reset + Foreground::LightRedEx + message;
}
