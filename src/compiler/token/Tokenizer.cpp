#include "Tokenizer.hpp"

namespace Compiler {
    /**
     * Initilaize the tokenizer.
     * @param data raw input data
     */
    Tokenizer::Tokenizer(String data) 
        : data(data)
    { }

    /**
     * Parse the next token from the data.
     * @return next parsed token
     */
    Token Tokenizer::next() {
        // ignore whitespaces
        while (isWhitespace(peek())) {
            // handle new line
            if (get() == '\n') {
                // reset the line index
                lineIndex = 0;
                return Token::of(TokenType::LineNumber, toString(++lineNumber));
            }
        }
        // handle content endxing
        if (peek() == '\0')
            return Token::of(TokenType::Finish);
        // handle identifiers
        else if (isIdentifierStart(peek()))
            return nextIdentifier();
        // handle operators
        else if (isOperator(peek()))
            return nextOperator();
        // handle separators
        else if (isSeparator(peek()))
            return nextSeparator();
        // handle numbers
        else if (isNumber(peek()))
            return nextNumber();
        // handle invalid syntax
        return Token::of(TokenType::Unexpected);
    }

    /**
     * Parse the next identifier token.
     * @return new identifier token
     */
    Token Tokenizer::nextIdentifier() {
        // get the full identifier
        uint begin = cursor;
        while (isIdentifierPart(peek())) 
            get();
        String token = range(begin, cursor);
        // determine the token type
        TokenType type = TokenType::Identifier;
        if (isExpression(token))
            type = TokenType::Expression;
        else if (isType(token))
            type = TokenType::Type;
        else if (isModifier(token))
            type = TokenType::Modifier;
        else if (isBoolean(token))
            type = TokenType::Boolean;
        else if (isInfo(token))
            type = TokenType::Info;
        else if (isNull(token))
            type = TokenType::Null;
        // make the identifier token
        return Token::of(type, token);
    }

    /**
     * Parse the next operator token.
     * @return new operator token
     */
    Token Tokenizer::nextOperator() {
        return Token(TokenType::Operator, String(1, get()));
    }

    /**
     * Parse the next separator token.
     * @return new separator token
     */
    Token Tokenizer::nextSeparator() {
        TokenType type = TokenType::Unexpected;
        switch (get()) {
            case ';':
                type = TokenType::Semicolon;
                break;
            case ':':
                type = TokenType::Colon;
                break;
            case ',':
                type = TokenType::Comma;
                break;
            case '{':
                type = TokenType::Begin;
                break;
            case '}':
                type = TokenType::End;
                break;
            case '(':
                type = TokenType::Open;
                break;
            case ')':
                type = TokenType::Close;
                break;
            case '[':
                type = TokenType::Start;
                break;
            case ']':
                type = TokenType::Stop;
                break;
        }
        return Token::of(type);
    }

    /**
     * Parse the next number token.
     * @return new number token
     */
    Token Tokenizer::nextNumber() {
        // get the beginning of the number content
        int begin = cursor;
        // determine if the number is integer
        bool integer = true;
        // handle hexadecimal numbers
        if (peek() == '0' && at(cursor + 1) == 'x') {
            // skip the '0x' prefix
            move(2);
            // handle number content
            while (isHexValue(peek()))
                get();
            // make the hexadecimal number token
            String value = range(begin, cursor);
            return Token::of(TokenType::Hexadecimal, value);
        }
        // handle regular number
        while (isNumberContent(upper(peek()))) {
            // handle floating point number
            if (peek() == '.') {
                // check if the floating-point number contains multiple dot symchols
                if (!integer)
                    return Token::of(TokenType::Unexpected, "Floating point number cannot have multiple dot symbols.");
                integer = false;
            }
            // check if a number type suffix is specified
            if (isNumberSuffix(upper(peek()))) {
                // get the type of the number
                TokenType type = integer ? TokenType::Integer : TokenType::Double;
                switch (upper(peek())) {
                    case 'B':
                        type = TokenType::Byte;
                        break;
                    case 'S':
                        type = TokenType::Short;
                        break;
                    case 'I':
                        type = TokenType::Integer;
                        break;
                    case 'L':
                        type = TokenType::Long;
                        break;
                    case 'F':
                        type = TokenType::Float;
                        break;
                    case 'D':
                        type = TokenType::Double;
                        break;
                }
                // check if integer type value has non-floating-point data
                if (!integer && (type == TokenType::Byte || type == TokenType::Short 
                        || type == TokenType::Integer || type == TokenType::Long)) {
                    return Token::of(TokenType::Unexpected, Token::getTokenName(type) + " cannot have a floating-point value.");
                }
                // skip the type specifier
                move(1);
                // get the value of the number
                String value = range(begin, cursor - 1);
                return Token::of(type, value); 
                // TODO check if number declaration ended because a type specifier were set, 
                //  but after the specifier there is no sperator or whitespace eg. 1.5Flol
            }
            // move to the next number part
            get();
        }
        // get the value of the number
        String value = range(begin, cursor);
        return Token::of(integer ? TokenType::Integer : TokenType::Double, value);
    }

    /**
     * Get the character at the current index.
     * @return currently parsed data index
     */
    char Tokenizer::peek() {
        return at(cursor);
    }

    /**
     * Get the character at the current index and move to the next position.
     * @return currently parsed data index
     */
    char Tokenizer::get() {
        return at(cursor++);
    }

    /**
     * Get the previous character from the data.
     * @return previously parsed character
     */
    char Tokenizer::prev() {
        return at(cursor - 1);
    }

    /**
     * Get the previous nth character from the data.
     * @param skip rewind amount
     * @return previous nth character
     */
    char Tokenizer::prev(uint skip) {
        return at(cursor - skip);
    }

    /**
     * Move the cursor with the given amount.
     * @param skip cursor move amount
     */
    void Tokenizer::move(uint skip) {
        cursor += skip;
    }

    /**
     * Determine if th egiven index is in bounds of the data size.
     * @param index target index to check
     * @return true if the index is in the parsed data
     */
    bool Tokenizer::has(uint index) {
        return index >= 0 && index < data.length();
    }

    /**
     * Get the character at the given index.
     * @param index target data index
     * @return character at the index or '\0' if it is out of the bounds
     */
    char Tokenizer::at(uint index) {
        return has(index) ? data[index] : '\0';
    }

    /**
     * Get the string value from the data within the given range.
     * @param begin data range start index
     * @param end data range finish index
     */
    String Tokenizer::range(uint begin, uint end) {
        String result;
        for (; begin < end; begin++)
            result += data[begin];
        return result;
    }

    /**
     * Check if the given character is a whitespace.
     * @param c target character to test
     * @return true if the character is a whitespace
     */
    bool Tokenizer::isWhitespace(char c) {
        switch (c) {
            case ' ':
            case '\t':
            case '\r':
            case '\n':
                return true;
            default:
                return false;
        }
    }

    /**
     * Check if the given character is the beginning of an identifier.
     * @param c target character to test
     * @return true if the character is an identifier beginning
     */
    bool Tokenizer::isIdentifierStart(char c) {
        return isalpha(c) || c == '_';
    }

    /**
     * Check if the given character is the part of an identifier.
     * @param c target character to test
     * @return true if the character is an identifier part
     */
    bool Tokenizer::isIdentifierPart(char c) {
        return isIdentifierStart(c) || isNumber(c);
    }

    /**
     * Check if the given character is numeric.
     * @param c target character to test
     * @return true if the character is numeric
     */
    bool Tokenizer::isNumber(char c) {
        return isdigit(c);
    }

    /**
     * Check if the given character is the ending of a number.
     * @param c target character to test
     * @return true if the character is a number suffix
     */
    bool Tokenizer::isNumberSuffix(char c) {
        switch (c) {
            case 'B':
            case 'S':
            case 'I':
            case 'L':
            case 'F':
            case 'l':
                return true;
            default:
                return false;
        }
    }

    /**
     * Check if the given character is a hexadecimal number part.
     * @param c target character to test
     * @return true if the character is a hexadecimal char
     */
    bool Tokenizer::isHexValue(char c) {
        switch (c) {
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
                return true;
            default:
                return isNumber(c);
        }
    }

    /**
     * Check if the given character is a content of a number.
     * @param c target character to test
     * @return true if the character is a number content
     */
    bool Tokenizer::isNumberContent(char c) {
        switch (c) {
            case '.':
            case '_':
                return true;
            default:
                return isHexValue(c) || isNumberSuffix(c);
        }
    }

    /**
     * Check if the given character is an operator.
     * @param c target character to test
     * @return true if the character is an operator
     */
    bool Tokenizer::isOperator(char c) {
        switch (c) {
            case '.':
            case '=':
            case '+':
            case '-':
            case '*':
            case '/':
            case '<':
            case '>':
            case '?':
            case '!':
            case '^':
            case '&':
            case '~':
                return true;
            default:
                return false;
        }
    }

    /**
     * Check if the given character is a separator.
     * @param c target character to test
     * @return true if the character is a separator
     */
    bool Tokenizer::isSeparator(char c) {
        switch (c) {
            case ';':
            case ':':
            case ',':
            case '{':
            case '}':
            case '(':
            case ')':
            case '[':
            case ']':
                return true;
            default:
                return false;
        }
    }

    /**
     * Check if the given token is an expression token.
     * @param c target character to test
     * @return true if the token is an expression
     */
    bool Tokenizer::isExpression(String token) {
        return token == "new"
            || token == "class"
            || token == "enum"
            || token == "interface"
            || token == "for"
            || token == "while"
            || token == "repeat"
            || token == "do"
            || token == "if"
            || token == "else"
            || token == "switch"
            || token == "case"
            || token == "loop"
            || token == "continue"
            || token == "break"
            || token == "return"
            || token == "await"
            || token == "goto"
            || token == "is"
            || token == "as";
    }

    /**
    * Check if the given token is a type token.
    * @param c target character to test
    * @return true if the token is a type
    */
    bool Tokenizer::isType(String token) {
        return token == "let"
            || token == "byte"
            || token == "short"
            || token == "int"
            || token == "double"
            || token == "float"
            || token == "long"
            || token == "void"
            || token == "boolean"
            || token == "char";
    }

    /**
    * Check if the given token is a modifier token.
    * @param c target character to test
    * @return true if the token is a modifier
    */
    bool Tokenizer::isModifier(String token) {
        return token == "public"
            || token == "protected"
            || token == "private"
            || token == "static"
            || token == "final"
            || token == "native"
            || token == "extern"
            || token == "volatile"
            || token == "transient"
            || token == "synchronized"
            || token == "async"
            || token == "const"
            || token == "unsafe"
            || token == "weak"
            || token == "strong"
            || token == "default";
    }

    /**
    * Check if the given token is a boolean token.
    * @param c target character to test
    * @return true if the token is a boolean
    */
    bool Tokenizer::isBoolean(String token) {
        return token == "true" || token == "false";
    }

    /**
    * Check if the given token is an information token.
    * @param c target character to test
    * @return true if the token is an information
    */
    bool Tokenizer::isInfo(String token) {
        return token == "package" || token == "import";
    }

    /**
    * Check if the given token is a null token.
    * @param c target character to test
    * @return true if the token is a null
    */
    bool Tokenizer::isNull(String token) {
        return token == "null" || token == "nullptr";
    }

    /**
     * Get the uppercase format of the given characetr.
     * @param c target character to be transformerd
     * @return uppercase representation of the character
     */
    char Tokenizer::upper(char c) {
        return toupper(c);
    }

    /**
     * Get the lowercase format of the given characetr.
     * @param c target character to be transformerd
     * @return lowercase representation of the character
     */
    char Tokenizer::lower(char c) {
        return tolower(c);
    }
}