#pragma once

#include "../../Common.hpp"

namespace Compiler {
    /**
     * Represents a registry of the token types.
     */
    enum class TokenType {
        String,      // "text"
        Character,   // 'A'
        Begin,       // {
        End,         // }
        Byte,        // 12B
        Short,       // 100S
        Double,      // 3.0D, 3.0
        Float,       // 1.5F
        Long,        // 123L
        Integer,     // 1337
        Hexadecimal, // 0xFFFFF
        Boolean,     // true
        Semicolon,   // ;
        Expression,  // class
        Colon,       // :
        Comma,       // ,
        Open,        // (
        Close,       // )
        Identifier,  // abc
        Operator,    // +
        Type,        // int
        Modifier,    // public
        Start,       // [
        Stop,        // ]
        Annotation,  // @Link
        LineNumber,  // L11
        Null,        // null
        Info,        // file information
        Finish,      // content finished
        Unexpected   // syntax error
    };

    /**
     * Represents a parsed token that holds a type and a string value for it.
     */
    class Token {
    public:
        /**
         * The type of the token.
         */
        TokenType type;

        /**
         * The value of the token.
         */
        String value;

        /**
         * Initialize the parsed token.
         * @param type token type
         * @param value token value
         */
        Token(TokenType type, String value);

        /**
         * Create a new token with the given type and value.
         * @param type token type
         * @param value token value
         * @return new parsed token
         */
        static Token of(TokenType type, String value);

        /**
         * Create a new token with the given type.
         * @param type token type
         * @return new parsed token
         */
        static Token of(TokenType type);

        /**
         * Get the name of the given token type.
         * @param type target token type
         * @return token type name
         */
        static String getTokenName(TokenType type);

        /**
         * Determine if this token is not a finish token.
         * @return true if there are more tokens to be parsed
         */
        bool hasNext();

        /**
         * Determine if this token has the given type.
         * @param type token type
         * @return true if this token has the type
         */
        bool is(TokenType type);

        /**
         * Determine if this token is one of the given types.
         * @param size parameter types
         * @param ... type varargs
         * @return true if this token has the type
         */
        bool is(uint size, TokenType...);

        /**
         * Determine if the token has the given value.
         * @param value token value
         * @return true if the token has the value
         */
        bool val(String value);
    };

    /**
     * Make the token type printable to the output stream.
     * @param stream console output stream
     * @param type target token type
     */
    OutputStream& operator<<(OutputStream& stream, const TokenType& type);

    /**
     * Make the token type printable to the output stream.
     * @param stream console output stream
     * @param token target token
     */
    OutputStream& operator<<(OutputStream& stream, Token& token);
}