#include "Tokenizer.hpp"
#include "../../util/Strings.hpp"

using namespace Void;

namespace Compiler {
    /**
     * Initilaize the tokenizer.
     * @param data raw input data
     */
    Tokenizer::Tokenizer(UString data) 
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
                lineNumber++;
                // make a new line token to be replaced later to semicolons
                return Token::of(TokenType::NewLine);
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
        // handle string literals
        else if (isString(peek()))
            return nextString();
        // handle char literals
        else if (isChar(peek()))
            return nextChar();
        // handle annotations
        else if (isAnnotation(peek()))
            return nextAnnotation();
        // handle invalid syntax
        syntaxError("");
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
        UString token = range(begin, cursor);
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
        return Token(TokenType::Operator, UString(1, get()));
    }

    /**
     * Parse the next separator token.
     * @return new separator token
     */
    Token Tokenizer::nextSeparator() {
        TokenType type = TokenType::Unexpected;
        cint c = get();
        switch (c) {
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
        return Token::of(type, UString(1, c));
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
            skip(2);
            // handle number content
            while (isHexValue(peek()))
                get();
            // make the hexadecimal number token
            UString value = range(begin, cursor);
            return Token::of(TokenType::Hexadecimal, value);
        }
        // handle regular number
        while (isNumberContent(upper(peek()))) {
            // handle floating point number
            if (peek() == '.') {
                // check if the floating-point number contains multiple dot symchols
                if (!integer)
                    return Token::of(TokenType::Unexpected, U"Floating point number cannot have multiple dot symbols.");
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
                    return Token::of(TokenType::Unexpected, Token::getTokenName(type) + U" cannot have a floating-point value.");
                }
                // skip the type specifier
                skip(1);
                // get the value of the number
                UString value = range(begin, cursor - 1);
                return Token::of(type, value);
                // TODO check if number declaration ended because a type specifier were set, 
                //  but after the specifier there is no sperator or whitespace eg. 1.5Flol
            }
            // move to the next number part
            skip(1);
        }
        // get the value of the number
        UString value = range(begin, cursor);
        return Token::of(integer ? TokenType::Integer : TokenType::Double, value);
    }

    /**
     * Parse the next string literal token.
     * @return new string token
     */
    Token Tokenizer::nextString() {
        return nextLiteral(true);
    }

    /**
     * Parse the next char literal token.
     * @return new char token
     */
    Token Tokenizer::nextChar() {
        return nextLiteral(false);
    }

    /**
     * Parse the next string or char literal token.
     * @param string true for string, false for char
     * @return new string or char token
     */
    Token Tokenizer::nextLiteral(bool string) {
        // declare the string literal content
        UString content;
        // skip the quotation mark
        skip(1);
        bool escapeNext = false;
        // loop until the string literal is terminated or the end of file has been reached
        while (has(cursor)) {
            // handle escaped characters
            if (escapeNext) {
                switch (peek()) {
                    case 'n':
                        content += '\n';
                        break;
                    case 'r':
                        content += '\r';
                        break;
                    case 't':
                        content += '\t';
                        break;
                    case '\\':
                        content += '\\';
                        break;
                        // TODO handle \u character code
                    default:
                        if ((string && peek() == '"') || (!string && peek() == '\''))
                            content += peek();
                        else
                            syntaxError("Invalid escape sequance: \\" + peek());
                }
                escapeNext = false;
            }
            // handle escaping the nex tcharacter
            else if (peek() == '\\')
                escapeNext = true;
            // handle the ending of the string literal
            else if ((peek() == '"' && string) || (peek() == '\'' && !string)) {
                // skip the end of the string
                skip(1);
                return Token::of(string ? TokenType::String : TokenType::Character, content);
            }
            // handle string literal content
            else
                content += peek();
            // move to the next string character
            skip(1);
        }
        syntaxError(String("Missing trailing `") + (string ? '"' : '\'') + "` symbol to terminate the " + (string ? "string" : "char") + " literal.");
        return Token::of(TokenType::Unexpected);
    }

    /**
     * Parse the next annotation token.
     * @return new annotation token
     */
    Token Tokenizer::nextAnnotation() {
        // skip the '@' symbol
        skip(1);
        // parse the name of the annotation
        Token token = nextIdentifier();
        // check for errors
        if (!token.is(TokenType::Identifier))
            return token;
        // create the annotation token
        return Token::of(TokenType::Annotation, token.value);
    }

    /**
     * Get the character at the current index.
     * @return currently parsed data index
     */
    cint Tokenizer::peek() {
        return at(cursor);
    }

    /**
     * Get the last non-whitespace character from the data.
     * @return last non-whitespace character
     */
    cint Tokenizer::peekNoWhitespace() {
        uint index = cursor;
        while (isWhitespace(at(index)))
            index--;
        return at(index);
    }

    /**
     * Get the character at the current index and move to the next position.
     * @return currently parsed data index
     */
    cint Tokenizer::get() {
        lineIndex++;
        return at(cursor++);
    }

    /**
     * Get the previous character from the data.
     * @return previously parsed character
     */
    cint Tokenizer::prev() {
        return at(cursor - 1);
    }

    /**
     * Get the previous nth character from the data.
     * @param skip rewind amount
     * @return previous nth character
     */
    cint Tokenizer::prev(uint skip) {
        return at(cursor - skip);
    }

    /**
     * Move the cursor with the given amount.
     * @param amount cursor move amount
     */
    void Tokenizer::skip(uint amount) {
        lineIndex += amount;
        cursor += amount;
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
    cint Tokenizer::at(uint index) {
        return has(index) ? data[index] : '\0';
    }

    /**
     * Get the string value from the data within the given range.
     * @param begin data range start index
     * @param end data range finish index
     */
    UString Tokenizer::range(uint begin, uint end) {
        UString result;
        for (; begin < end; begin++)
            result += data[begin];
        return result;
    }

    /**
     * Check if the given character is a whitespace.
     * @param c target character to test
     * @return true if the character is a whitespace
     */
    bool Tokenizer::isWhitespace(cint c) {
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
    bool Tokenizer::isIdentifierStart(cint c) {
        return iswalpha((wint_t) c) || c == '_';
    }

    /**
     * Check if the given character is the part of an identifier.
     * @param c target character to test
     * @return true if the character is an identifier part
     */
    bool Tokenizer::isIdentifierPart(cint c) {
        return isIdentifierStart(c) || isNumber(c);
    }

    /**
     * Check if the given character is numeric.
     * @param c target character to test
     * @return true if the character is numeric
     */
    bool Tokenizer::isNumber(cint c) {
        return iswdigit((wint_t) c);
    }

    /**
     * Check if the given character is the beginning of a string.
     * @param c target character to test
     * @return true if the character is a string beginning
     */
    bool Tokenizer::isString(cint c) {
        return c == '"';
    }

    /**
     * Check if the given character is the beginning of a char.
     * @param c target character to test
     * @return true if the character is a char beginning
     */
    bool Tokenizer::isChar(cint c) {
        return c == '\'';
    }

    /**
     * Check if the given character is the beginning of an annotaion.
     * @param c target character to test
     * @return true if the character is an annotation beginning
     */
    bool Tokenizer::isAnnotation(cint c) {
        return c == '@';
    }

    /**
     * Check if the given character is the ending of a number.
     * @param c target character to test
     * @return true if the character is a number suffix
     */
    bool Tokenizer::isNumberSuffix(cint c) {
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
    bool Tokenizer::isHexValue(cint c) {
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
    bool Tokenizer::isNumberContent(cint c) {
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
    bool Tokenizer::isOperator(cint c) {
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
            case '$':
            case '|':
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
    bool Tokenizer::isSeparator(cint c) {
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
    bool Tokenizer::isExpression(UString token) {
        return token == U"new"
            || token == U"class"
            || token == U"struct"
            || token == U"enum"
            || token == U"interface"
            || token == U"for"
            || token == U"while"
            || token == U"repeat"
            || token == U"do"
            || token == U"if"
            || token == U"else"
            || token == U"switch"
            || token == U"case"
            || token == U"loop"
            || token == U"continue"
            || token == U"break"
            || token == U"return"
            || token == U"await"
            || token == U"goto"
            || token == U"is"
            || token == U"as"
            || token == U"where"
            || token == U"defer";
    }

    /**
     * Check if the given token is a type token.
     * @param c target character to test
     * @return true if the token is a type
     */
    bool Tokenizer::isType(UString token) {
        return token == U"let"
            || token == U"byte"
            || token == U"short"
            || token == U"int"
            || token == U"double"
            || token == U"float"
            || token == U"long"
            || token == U"void"
            || token == U"bool"
            || token == U"char"
            || token == U"string";
    }

    /**
    * Check if the given token is a modifier token.
    * @param c target character to test
    * @return true if the token is a modifier
    */
    bool Tokenizer::isModifier(UString token) {
        return token == U"public"
            || token == U"protected"
            || token == U"private"
            || token == U"static"
            || token == U"final"
            || token == U"native"
            || token == U"extern"
            || token == U"volatile"
            || token == U"transient"
            || token == U"synchronized"
            || token == U"async"
            || token == U"const"
            || token == U"unsafe"
            || token == U"weak"
            || token == U"strong"
            || token == U"default";
    }

    /**
    * Check if the given token is a boolean token.
    * @param c target character to test
    * @return true if the token is a boolean
    */
    bool Tokenizer::isBoolean(UString token) {
        return token == U"true" || token == U"false";
    }

    /**
    * Check if the given token is an information token.
    * @param c target character to test
    * @return true if the token is an information
    */
    bool Tokenizer::isInfo(UString token) {
        return token == U"package" || token == U"import";
    }

    /**
    * Check if the given token is a null token.
    * @param c target character to test
    * @return true if the token is a null
    */
    bool Tokenizer::isNull(UString token) {
        return token == U"null" || token == U"nullptr";
    }

    /**
     * Get the uppercase format of the given characetr.
     * @param c target character to be transformerd
     * @return uppercase representation of the character
     */
    cint Tokenizer::upper(cint c) {
        return toupper(c);
    }

    /**
     * Get the lowercase format of the given characetr.
     * @param c target character to be transformerd
     * @return lowercase representation of the character
     */
    cint Tokenizer::lower(cint c) {
        return tolower(c);
    }

    /**
     * Display a syntax error in the console with debug information.
     * @param message error message
     */
    void Tokenizer::syntaxError(String message) {
        // debug the error message
        println("SyntaxError: Unexpected char '" << Strings::fromUTF(peekNoWhitespace()) << "' in line " << lineNumber << " at index " << lineIndex);
        if (message.length() > 0)
            println(message);

        // get the line from the data where the error has occurred at
        UString line = Strings::split(data, '\n')[lineNumber - 1];
        
        ulong length = line.length();
        ulong beginCut = 0;
        // check if the line is longer than the max line display length
        if (length > MAX_ERROR_LINE_LENGTH) {
            // get how many extra characters are in the line
            ulong extra = length - MAX_ERROR_LINE_LENGTH;
            // remov ethe extra ending of the line
            line = line.substr(0, length - extra / 2);
            // calculate how muc hshould be removed from the beginning
            beginCut = getMax(extra / 2 - 1, 0);
            // remove the extra beginning of the line
            line = line.substr(beginCut);
        }

        // debug the line with the error
        println(Strings::fromUTF(line));
    
        // debug a pointer to at the invalid character
        for (ulong i = 0; i < lineIndex - beginCut; i++)
            print(" ");
        // move the pointer to the correct position
        uint index = lineIndex;
        while (index < line.length() && line[index++] != peek())
            print(" ");
        // debug the pointer itself
        println("^");
    }

    /**
     * Auto-insert new lines at the end of lines if it is required.s
     * @param source raw tokens input
     * @return converted tokens output
     */
    List<Token> Tokenizer::insertSemicolons(List<Token> source) {
        List<Token> output;

        Token lastToken = Token::of(TokenType::None);
        

        return output;
    }
}