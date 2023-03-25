#pragma once

#include "Token.hpp"
#include "../../util/Lists.hpp"

namespace Compiler {
    /**
     * Represents a utility that parses raw string input to tokens.
     */
    class Tokenizer {
    private:
        /**
         * The input data of the tokenizer.
         */
        String data;

        /**
         * The current index of the data.
         */
        uint cursor = 0;

        /**
         * The index of the current character in the line being processed.
         */
        uint lineIndex;

        /**
         * The number of the current line being processed.
         */
        uint lineNumber;

    public:
        /**
         * Initilaize the tokenizer.
         * @param data raw input data
         */
        Tokenizer(String data);

        /**
         * Parse the next token from the data.
         * @return next parsed token
         */
        Token next();

        /**
         * Parse the next identifier token.
         * @return new identifier token
         */
        Token nextIdentifier();

        /**
         * Parse the next operator token.
         * @return new operator token
         */
        Token nextOperator();

        /**
         * Parse the next separator token.
         * @return new separator token
         */
        Token nextSeparator();

        /**
         * Parse the next number token.
         * @return new number token
         */
        Token nextNumber();

        /**
         * Get the character at the current index.
         * @return currently parsed data index
         */
        char peek();

        /**
         * Get the character at the current index and move to the next position.
         * @return currently parsed data index
         */
        char get();

        /**
         * Get the previous character from the data.
         * @return previously parsed character
         */
        char prev();

        /**
         * Get the previous nth character from the data.
         * @param skip rewind amount
         * @return previous nth character
         */
        char prev(uint skip);

        /**
         * Move the cursor with the given amount.
         * @param skip cursor move amount
         */
        void move(uint skip);

        /**
         * Determine if th egiven index is in bounds of the data size.
         * @param index target index to check
         * @return true if the index is in the parsed data
         */
        bool has(uint index);

        /**
         * Get the character at the given index.
         * @param index target data index
         * @return character at the index or '\0' if it is out of the bounds
         */
        char at(uint index);

        /**
         * Get the string value from the data within the given range.
         * @param begin data range start index
         * @param end data range finish index
         */
        String range(uint begin, uint end);

        /**
         * Check if the given character is a whitespace.
         * @param c target character to test
         * @return true if the character is a whitespace
         */
        bool isWhitespace(char c);

        /**
         * Check if the given character is the beginning of an identifier.
         * @param c target character to test
         * @return true if the character is an identifier beginning
         */
        bool isIdentifierStart(char c);
    
        /**
         * Check if the given character is the part of an identifier.
         * @param c target character to test
         * @return true if the character is an identifier part
         */
        bool isIdentifierPart(char c);

        /**
         * Check if the given character is numeric.
         * @param c target character to test
         * @return true if the character is numeric
         */
        bool isNumber(char c);

        /**
         * Check if the given character is the ending of a number.
         * @param c target character to test
         * @return true if the character is a number suffix
         */
        bool isNumberSuffix(char c);

        /**
         * Check if the given character is a hexadecimal number part.
         * @param c target character to test
         * @return true if the character is a hexadecimal char
         */
        bool isHexValue(char c);

        /**
         * Check if the given character is a content of a number.
         * @param c target character to test
         * @return true if the character is a number content
         */
        bool isNumberContent(char c);

        /**
         * Check if the given character is an operator.
         * @param c target character to test
         * @return true if the character is an operator
         */
        bool isOperator(char c);

        /**
         * Check if the given character is a separator.
         * @param c target character to test
         * @return true if the character is a separator
         */
        bool isSeparator(char c);

        /**
         * Check if the given token is an expression token.
         * @param c target character to test
         * @return true if the token is an expression
         */
        bool isExpression(String token);

        /**
        * Check if the given token is a type token.
        * @param c target character to test
        * @return true if the token is a type
        */
        bool isType(String token);

        /**
        * Check if the given token is a modifier token.
        * @param c target character to test
        * @return true if the token is a modifier
        */
        bool isModifier(String token);

        /**
        * Check if the given token is a boolean token.
        * @param c target character to test
        * @return true if the token is a boolean
        */
        bool isBoolean(String token);

        /**
        * Check if the given token is an information token.
        * @param c target character to test
        * @return true if the token is an information
        */
        bool isInfo(String token);

        /**
        * Check if the given token is a null token.
        * @param c target character to test
        * @return true if the token is a null
        */
        bool isNull(String token);

        /**
         * Get the uppercase format of the given characetr.
         * @param c target character to be transformerd
         * @return uppercase representation of the character
         */
        char upper(char c);

        /**
         * Get the lowercase format of the given characetr.
         * @param c target character to be transformerd
         * @return lowercase representation of the character
         */
        char lower(char c);
    };
}