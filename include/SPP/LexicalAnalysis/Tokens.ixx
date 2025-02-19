module;
#include <string>

export module spp.lexical_analysis.tokens;


export namespace SPP::LexicalAnalysis {
    enum class RawTokenTypes;
    enum class TokenTypes;
    struct RawToken;
}


/**
 * A list of all the different individual tokens that can be found in the source code.
 */
enum class SPP::LexicalAnalysis::RawTokenTypes {
    TkCharacter,
    TkNumber,
    TkEqualsSign,
    TkPlusSign,
    TkMinusSign,
    TkAsterisk,
    TkForwardSlash,
    TkPercentSign,
    TkCaret,
    TkLessThanSign,
    TkGreaterThanSign,
    TkLeftParenthesis,
    TkRightParenthesis,
    TkLeftSquareBracket,
    TkRightSquareBracket,
    TkLeftCurlyBrace,
    TkRightCurlyBrace,
    TkQuestionMark,
    TkColon,
    TkAmpersand,
    TkVerticalBar,
    TkDot,
    TkComma,
    TkAt,
    TkUnderscore,
    TkSpeechMark,
    TkWhitespace,
    TkNewLine,
    TkDollar,
    TkUnknown,
    TkExclamationMark,
    NoToken,
    Keyword,
    EndOfFile,
};

/**
 * A list of all the different keywords that are broken down into individual characters in the parser.
 */
enum class SPP::LexicalAnalysis::TokenTypes {
    LxIdentifier,
    LxUpperIdentifier,
    LxBinDigits,
    LxHexDigits,
    LxDecInteger,
    LxDoubleQuoteStr,
    LxMultiLineComment,
    LxSingleLineComment,

    KwCls,
    KwSup,
    KwFun,
    KwCor,
    KwUse,
    KwExt,
    KwCmp,
    KwLet,
    KwMut,
    KwPin,
    KwRel,
    KwCase,
    KwElse,
    KwLoop,
    KwWith,
    KwSkip,
    KwExit,
    KwStep,
    KwRet,
    KwGen,
    KwWhere,
    KwAs,
    KwIsNot,
    KwIs,
    KwTrue,
    KwFalse,
    KwSelfVal,
    KwSelfType,
    KwAnd,
    KwOr,
    KwNot,
    KwOf,
    KwIn,
    KwAsync,

    TkEquals,
    TkNotEquals,
    TkLessThanOrEqual,
    TkGreaterThanOrEqual,
    TkLessThan,
    TkGreaterThan,
    TkSpaceship,
    TkPlus,
    TkMinus,
    TkAsterisk,
    TkForwardSlash,
    TkPercent,
    TkDoublePercent,
    TkExponent,
    TkPlusEquals,
    TkMinusEquals,
    TkAsteriskEquals,
    TkForwardSlashEquals,
    TkPercentEquals,
    TkDoublePercentEquals,
    TkExponentEquals,
    TkLeftParenthesis,
    TkRightParenthesis,
    TkLeftBracket,
    TkRightBracket,
    TkLeftBrace,
    TkRightBrace,
    TkQuestionMark,
    TkDoubleDot,
    TkColon,
    TkAmpersand,
    TkVerticalBar,
    TkDot,
    TkDoubleColon,
    TkComma,
    TkAssign,
    TkRightwardsArrow,
    TkAt,
    TkSpeechMark,
    TkUnderscore,
    TkWhitespace,
    TkNewLine,
    TkDollar,

    NoToken,
    EndOfFile,
};


/**
 * A class representing a token in the source code, and any associated metadata.
 */
struct SPP::LexicalAnalysis::RawToken {
    RawTokenTypes tok_type;
    char tok_metadata;

    auto operator==(const RawToken &other) const -> bool {
        return tok_type == other.tok_type;
    }
};



