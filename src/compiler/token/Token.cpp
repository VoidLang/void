#include "Token.hpp"

namespace Compiler {
    /**
     * Initialize the parsed token.
     * @param type token type
     * @param value token value
     */
    Token::Token(TokenType type, String value)
        : type(type), value(value)
    { }

    /**
     * Create a new token with the given type and value.
     * @param type token type
     * @param value token value
     * @return new parsed token
     */
    Token Token::of(TokenType type, String value) {
        return Token(type, value);
    }

    /**
     * Create a new token with the given type.
     * @param type token type
     * @return new parsed token
     */
    Token Token::of(TokenType type) {
        return Token(type, "");
    }

    /**
     * Get the name of the given token type.
     * @param type target token type
     * @return token type name
     */
    String Token::getTokenName(TokenType type) {
        // declare a static array of the token type names
        static const char* const names[]{
            "String",
            "Character",
            "Begin",
            "End",
            "Byte",
            "Short",
            "Double",
            "Float",
            "Long",
            "Integer",
            "Hexadecimal",
            "Boolean",
            "Semicolon",
            "Expression",
            "Colon",
            "Comma",
            "Open",
            "Close",
            "Identifier",
            "Operator",
            "Type",
            "Modifier",
            "Start",
            "Stop",
            "Annotation",
            "LineNumber",
            "Null",
            "Finish",
            "Unexpected"
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
    bool Token::val(String value) {
        return this->value == value;
    }

    /**
     * Make the token type printable to the output stream.
     * @param stream console output stream
     * @param type target token type
     */
    OutputStream& operator<<(OutputStream& stream, const TokenType& type) {
        // write the token type to the output stream
        return stream << Token::getTokenName(type);
    }

    /**
     * Make the token type printable to the output stream.
     * @param stream console output stream
     * @param token target token
     */
    OutputStream& operator<<(OutputStream& stream, Token& token) {
        return stream << token.type << (!token.value.empty() ? (" |" + token.value + "|") : "");
    }
}