#pragma once

#include "Token.hpp"
#include "../../util/Lists.hpp"

namespace Compiler {
    /**
     * The maximum length of a displayable line of code in a syntax error.
     */
    const uint MAX_ERROR_LINE_LENGTH = 30;

    /**
     * Represents a utility that parses raw string input to tokens.
     */
    class Tokenizer {
    private:
        /**
         * The input data of the tokenizer.
         */
        UString data;

        /**
         * The current index of currently parsed character.
         */
        uint cursor = 0;

        /**
         * The index of the current character in the line being processed.
         */
        uint lineIndex = 0;

        /**
         * The number of the current line being processed.
         */
        uint lineNumber = 1;

        /**
         * The last token that has been parsed.
         */
        Token lastToken = Token::of(TokenType::None);

    public:
        /**
         * Initilaize the tokenizer.
         * @param data raw input data
         */
        Tokenizer(UString data);

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
         * Parse the next string literal token.
         * @return new string token
         */
        Token nextString();

        /**
         * Parse the next char literal token.
         * @return new char token
         */
        Token nextChar();

        /**
         * Parse the next annotation token.
         * @return new annotation token
         */
        Token nextAnnotation();

        /**
         * Parse the next string or char literal token.
         * @param string true for string, false for char
         * @return new string or char token
         */
        Token nextLiteral(bool string);

        /**
         * Get the character at the current index.
         * @return currently parsed data index
         */
        cint peek();

        /**
         * Get the last non-whitespace character from the data.
         * @return last non-whitespace character
         */
        cint peekNoWhitespace();

        /**
         * Get the character at the current index and move to the next position.
         * @return currently parsed data index
         */
        cint get();

        /**
         * Get the previous character from the data.
         * @return previously parsed character
         */
        cint prev();

        /**
         * Get the previous nth character from the data.
         * @param skip rewind amount
         * @return previous nth character
         */
        cint prev(uint skip);

        /**
         * Move the cursor with the given amount.
         * @param amount cursor move amount
         */
        void skip(uint amount);

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
        cint at(uint index);

        /**
         * Get the string value from the data within the given range.
         * @param begin data range start index
         * @param end data range finish index
         */
        UString range(uint begin, uint end);

        /**
         * Check if the given character is a whitespace.
         * @param c target character to test
         * @return true if the character is a whitespace
         */
        bool isWhitespace(cint c);

        /**
         * Check if the given character is the beginning of an identifier.
         * @param c target character to test
         * @return true if the character is an identifier beginning
         */
        bool isIdentifierStart(cint c);
    
        /**
         * Check if the given character is the part of an identifier.
         * @param c target character to test
         * @return true if the character is an identifier part
         */
        bool isIdentifierPart(cint c);

        /**
         * Check if the given character is numeric.
         * @param c target character to test
         * @return true if the character is numeric
         */
        bool isNumber(cint c);

        /**
         * Check if the given character is the beginning of a string.
         * @param c target character to test
         * @return true if the character is a string beginning
         */
        bool isString(cint c);

        /**
         * Check if the given character is the beginning of a chat.
         * @param c target character to test
         * @return true if the character is a char beginning
         */
        bool isChar(cint c);

        /**
         * Check if the given character is the beginning of an annotaion.
         * @param c target character to test
         * @return true if the character is an annotation beginning
         */
        bool isAnnotation(cint c);

        /**
         * Check if the given character is the ending of a number.
         * @param c target character to test
         * @return true if the character is a number suffix
         */
        bool isNumberSuffix(cint c);

        /**
         * Check if the given character is a hexadecimal number part.
         * @param c target character to test
         * @return true if the character is a hexadecimal char
         */
        bool isHexValue(cint c);

        /**
         * Check if the given character is a content of a number.
         * @param c target character to test
         * @return true if the character is a number content
         */
        bool isNumberContent(cint c);

        /**
         * Check if the given character is an operator.
         * @param c target character to test
         * @return true if the character is an operator
         */
        bool isOperator(cint c);

        /**
         * Check if the given character is a separator.
         * @param c target character to test
         * @return true if the character is a separator
         */
        bool isSeparator(cint c);

        /**
         * Check if the given token is an expression token.
         * @param c target character to test
         * @return true if the token is an expression
         */
        bool isExpression(UString token);

        /**
        * Check if the given token is a type token.
        * @param c target character to test
        * @return true if the token is a type
        */
        bool isType(UString token);

        /**
        * Check if the given token is a modifier token.
        * @param c target character to test
        * @return true if the token is a modifier
        */
        bool isModifier(UString token);

        /**
        * Check if the given token is a boolean token.
        * @param c target character to test
        * @return true if the token is a boolean
        */
        bool isBoolean(UString token);

        /**
        * Check if the given token is an information token.
        * @param c target character to test
        * @return true if the token is an information
        */
        bool isInfo(UString token);

        /**
        * Check if the given token is a null token.
        * @param c target character to test
        * @return true if the token is a null
        */
        bool isNull(UString token);

        /**
         * Get the uppercase format of the given characetr.
         * @param c target character to be transformerd
         * @return uppercase representation of the character
         */
        cint upper(cint c);

        /**
         * Get the lowercase format of the given characetr.
         * @param c target character to be transformerd
         * @return lowercase representation of the character
         */
        cint lower(cint c);

        /**
         * Display a syntax error in the console with debug information.
         * @param message error message
         */
        void syntaxError(String message);

        /**
         * Auto-insert new lines at the end of lines if it is required.s
         * @param source raw tokens input
         * @return converted tokens output
         */
        List<Token> insertSemicolons(List<Token> source);
   };
}