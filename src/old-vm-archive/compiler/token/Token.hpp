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
        Unexpected,  // syntax error,
        NewLine,     // temp new line, to be replaced by semicolons or be cleared
        None         // no such token
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
        UString value;

        /**
         * Initialize the parsed token.
         * @param type token type
         * @param value token value
         */
        Token(TokenType type, UString value);

        /**
         * Create a new token with the given type and value.
         * @param type token type
         * @param value token value
         * @return new parsed token
         */
        static Token of(TokenType type, UString value);

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
        static UString getTokenName(TokenType type);

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
         * Determine if this token has any of the given types.
         * @param length of target token types
         * @return true if this token has the type
         */
        bool is(uint size, ...);

        /**
         * Determine if the token has the given value.
         * @param value token value
         * @return true if the token has the value
         */
        bool val(UString value);

        /**
         * Determine if this token has the given type and value.
         * @param type token type
         * @param value token value
         * @return true if the type and value matches
         */
        bool is(TokenType type, UString value);

        /**
         * Determine if token matches the data of the other token.
         * @param other other token to check
         * @return true if the two tokens match
         */
        bool eq(Token other);

        /**
         * Determine if the type of this token is a number.
         * @return true if this token is a number
         */
        bool isNumber();

        /**
         * Determine if the type of this token is a literal token type.
         * @return true if this token is a constant literal
         */
        bool isLiteral();
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

    /**
     * Make UTF-32 String printable to the console.
     * @param stream console output stream
     * @param string target string
     */
    OutputStream& operator<<(OutputStream& stream, UString string);
}