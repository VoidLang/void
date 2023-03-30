#include "Transformer.hpp"

namespace Compiler {
    /**
     * Initialize the transformer
     * @param tokens input tokens
     */
    Transformer::Transformer(List<Token> tokens) 
        : tokens(tokens)
    { }

    /**
     * Apply the transformer on the tokens.
     * @return token list with inserted semicolons
     */
    List<Token> Transformer::transform() {
        List<Token> result;
        // transform tokens while there are more to be parsed
        while (hasNext()) {
            // update the currently parsed tokens
            update();
            handleCommandLine();
            handleCommandBlock();
            // ignore the token if it is not a new line
            if (!token.is(TokenType::NewLine)) {
                result.push_back(token);
                continue;
            }
            // check if the token before is one of the required tokens
            bool requiredBefore = false;
            for (Token element : REQUIRED_BEFORE) {
                if (equals(element, lastToken)) {
                    requiredBefore = true;
                    break;
                }
            }
            // check if the token after is one of the forbidden tokens
            bool forbiddenAfter = false;
            for (Token element : FORBIDDEN_AFTER) {
                if (equals(element, nextToken)) {
                    forbiddenAfter = true;
                    break;
                }
            }
            // place a semicolon if the token before the new line is one of the registered tokens, 
            // and the token after the new line is not one of the forbidden tokens
            if (requiredBefore && !forbiddenAfter)
                result.push_back(Token::of(TokenType::Semicolon));
            // if the requirements do not meet, we are just going to ignore the token
            // there is no need to put a semicolon, because it seems like the expression
            // continues
            // eg: 
            // database.fetchUser() <- new line detected, but a "." follows the token, do not place semicolon
            //     .then(|user| println("hi"))
            // return "hello" <- end of method declaration, place a semicolon after
        }
        return result;
    }

    /**
     * Update the currently parsed tokens.
     */
    void Transformer::update() {
        token = safeGet(cursor);
        lastToken = safeGet(cursor - 1);
        nextToken = safeGet(cursor + 1);
        cursor++;
    }

    /**
     * Check if two tokens are equals. Ignore value checking for certain token types.
     * @param left first token to check
     * @param right second token to check
     * @return true if the two tokens are equals
     */
    bool Transformer::equals(Token left, Token right) {
        // make sure both the tokens has the same type
        if (left.type != right.type)
            return false;
        switch (left.type) {
            // some tokens' values must be checked as well
            case TokenType::Operator:
            case TokenType::Expression:
                return left.value == right.value;
            default:
                return true;
        }
    }

    /**
     * Safely get the token at the given index.
     * @return token at the given index
     */
    Token Transformer::safeGet(uint index) {
        return index >= 0 && index < tokens.size() ? tokens[index] : Token::of(TokenType::None);
    }

    /**
     * Determine if there are more tokens to be parsed.
    * @return true if there are more tokens
    */
    bool Transformer::hasNext() {
        return cursor >= 0 && cursor < tokens.size();
    }

    /**
     * Ignore tokens that belong to a line of comment.
     */
    void Transformer::handleCommentLine() {
        // check for line command start
        if (!token.is(TokenType::Operator, U"/") || !nextToken.is(TokenType::Operator, U"/"))
            return;
        // loop unti a new line has started
        while (true) {
            Token token = safeGet(cursor++);
            if (token.is(TokenType::NewLine)) {
                update();
                return;
            }
        }
    }

    /**
     * Ignore tokens that belong to a block of comments..
     */
    void Transformer::handleCommentBlock() {
        // check for block command start
        if (!token.is(TokenType::Operator, U"/") || !nextToken.is(TokenType::Operator, U"*"))
            return;
        // loop until the comment block is ended
        while (true) {
            Token first = safeGet(cursor++);
            Token second = safeGet(cursor++);
            if (first.is(TokenType::Operator, U"*") && second.is(TokenType::Operator, U"/")) {
                update();
                return;
            }
        }
    }
}