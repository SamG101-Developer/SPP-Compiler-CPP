module;
#include <string_view>

module spp.lexical_analysis.lexer;
import spp.lexical_analysis.tokens;


SPP::LexicalAnalysis::Lexer::Lexer(const std::string_view code) : code(code) {
}


auto SPP::LexicalAnalysis::Lexer::Lex() const -> std::vector<RawToken> {
    auto tokens = std::vector<RawToken>{};
    auto in_string = false;

    for (const auto c : code) {
        if (in_string and c != '"') {
            tokens.emplace_back(RawTokenTypes::TkCharacter, c);
            continue;
        }

        switch (c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            tokens.emplace_back(RawTokenTypes::TkNumber, c);
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
            tokens.emplace_back(RawTokenTypes::TkCharacter, c);
            break;
        case '=':
            tokens.emplace_back(RawTokenTypes::TkEqualsSign, c);
            break;
        case '+':
            tokens.emplace_back(RawTokenTypes::TkPlusSign, c);
            break;
        case '-':
            tokens.emplace_back(RawTokenTypes::TkMinusSign, c);
            break;
        case '*':
            tokens.emplace_back(RawTokenTypes::TkAsterisk, c);
            break;
        case '/':
            tokens.emplace_back(RawTokenTypes::TkForwardSlash, c);
            break;
        case '%':
            tokens.emplace_back(RawTokenTypes::TkPercentSign, c);
            break;
        case '^':
            tokens.emplace_back(RawTokenTypes::TkCaret, c);
            break;
        case '<':
            tokens.emplace_back(RawTokenTypes::TkLessThanSign, c);
            break;
        case '>':
            tokens.emplace_back(RawTokenTypes::TkGreaterThanSign, c);
            break;
        case '(':
            tokens.emplace_back(RawTokenTypes::TkLeftParenthesis, c);
            break;
        case ')':
            tokens.emplace_back(RawTokenTypes::TkRightParenthesis, c);
            break;
        case '[':
            tokens.emplace_back(RawTokenTypes::TkLeftSquareBracket, c);
            break;
        case ']':
            tokens.emplace_back(RawTokenTypes::TkRightSquareBracket, c);
            break;
        case '{':
            tokens.emplace_back(RawTokenTypes::TkLeftCurlyBrace, c);
            break;
        case '}':
            tokens.emplace_back(RawTokenTypes::TkRightCurlyBrace, c);
            break;
        case '?':
            tokens.emplace_back(RawTokenTypes::TkQuestionMark, c);
            break;
        case ':':
            tokens.emplace_back(RawTokenTypes::TkColon, c);
            break;
        case '&':
            tokens.emplace_back(RawTokenTypes::TkAmpersand, c);
            break;
        case '|':
            tokens.emplace_back(RawTokenTypes::TkVerticalBar, c);
            break;
        case '.':
            tokens.emplace_back(RawTokenTypes::TkDot, c);
            break;
        case ',':
            tokens.emplace_back(RawTokenTypes::TkComma, c);
            break;
        case '@':
            tokens.emplace_back(RawTokenTypes::TkAt, c);
            break;
        case '_':
            tokens.emplace_back(RawTokenTypes::TkUnderscore, c);
            break;
        case '"':
            tokens.emplace_back(RawTokenTypes::TkSpeechMark, c);
            in_string = !in_string;
            break;
        case '$':
            tokens.emplace_back(RawTokenTypes::TkDollar, c);
            break;
        case ' ':
            tokens.emplace_back(RawTokenTypes::TkWhitespace, c);
            break;
        case '\n':
            tokens.emplace_back(RawTokenTypes::TkNewLine, c);
            break;
        case '!':
            tokens.emplace_back(RawTokenTypes::TkExclamationMark, c);
            break;
        case '\r':
            continue;
        default:
            tokens.emplace_back(RawTokenTypes::TkUnknown, c);
        }
    }

    tokens.emplace_back(RawTokenTypes::EndOfFile, '\0');
    return tokens;
}
