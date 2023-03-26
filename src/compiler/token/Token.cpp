#include "Token.hpp"
#include "../../util/Strings.hpp"

using namespace Void;

namespace Compiler {
    /**
     * Initialize the parsed token.
     * @param type token type
     * @param value token value
     */
    Token::Token(TokenType type, UString value)
        : type(type), value(value)
    { }

    /**
     * Create a new token with the given type and value.
     * @param type token type
     * @param value token value
     * @return new parsed token
     */
    Token Token::of(TokenType type, UString value) {
        return Token(type, value);
    }

    /**
     * Create a new token with the given type.
     * @param type token type
     * @return new parsed token
     */
    Token Token::of(TokenType type) {
        return Token(type, U"");
    }

    /**
     * Get the name of the given token type.
     * @param type target token type
     * @return token type name
     */
    UString Token::getTokenName(TokenType type) {
        // declare a static array of the token type names
        static const char32_t* const names[]{
            U"String",
            U"Character",
            U"Begin",
            U"End",
            U"Byte",
            U"Short",
            U"Double",
            U"Float",
            U"Long",
            U"Integer",
            U"Hexadecimal",
            U"Boolean",
            U"Semicolon",
            U"Expression",
            U"Colon",
            U"Comma",
            U"Open",
            U"Close",
            U"Identifier",
            U"Operator",
            U"Type",
            U"Modifier",
            U"Start",
            U"Stop",
            U"Annotation",
            U"LineNumber",
            U"Null",
            U"Finish",
            U"Unexpected"
        };
        // write the token type to the output stream
        return names[static_cast<int>(type)];
    }

    /**
     * Determine if this token is not a finish token.
     * @return true if there are more tokens to be parsed
     */
    bool Token::hasNext() {
        return type != TokenType::Finish
            && type != TokenType::Unexpected;
    }

    /**
     * Determine if this token has the given type.
     * @param type token type
     * @return true if this token has the type
     */
    bool Token::is(TokenType type) {
        return this->type == type;
    }

    /**
     * Determine if this token is one of the given types.
     * @param size parameter types
     * @param ... type varargs
     * @return true if this token has the type
     */
    bool Token::is(uint size, TokenType...) {
        // begin the processing of the varargs
        va_list list;
        va_start(list, size);

        // handle vararg parameters
        for (uint i = 0; i < size; i++) {
            if (va_arg(list, TokenType) == this->type)
                return true;
        }

        // end varargs processing
        va_end(list);
        return false;
    }

    /**
     * Determine if the token has the given value.
     * @param value token value
     * @return true if the token has the value
     */
    bool Token::val(UString value) {
        return this->value == value;
    }

    /**
     * Make the token type printable to the output stream.
     * @param stream console output stream
     * @param type target token type
     */
    OutputStream& operator<<(OutputStream& stream, const TokenType& type) {
        // write the token type to the output stream
        UString name = Token::getTokenName(type);
        return stream << Strings::fromUTF(name);
    }

    /**
     * Make the token type printable to the output stream.
     * @param stream console output stream
     * @param token target token
     */
    OutputStream& operator<<(OutputStream& stream, Token& token) {
        return stream << token.type << (!token.value.empty() ? (" |" + Strings::fromUTF(token.value) + "|") : "");
    }
}