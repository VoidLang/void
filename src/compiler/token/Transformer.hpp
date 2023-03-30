#pragma once

#include "../../Common.hpp"
#include "Token.hpp"

namespace Compiler {
    /**
     * Represents a token transformer that automatically inserts semicolons at the end of lines when it is required.
     */
    class Transformer {
        /**
         * The array of tokens required before the new line for the semicolon to be inserted.
         */
        const Token REQUIRED_BEFORE[20] = { 
            Token::of(TokenType::Identifier),
            Token::of(TokenType::String),
            Token::of(TokenType::Character),
            Token::of(TokenType::Byte),
            Token::of(TokenType::Short),
            Token::of(TokenType::Double),
            Token::of(TokenType::Float),
            Token::of(TokenType::Long),
            Token::of(TokenType::Integer),
            Token::of(TokenType::Hexadecimal),
            Token::of(TokenType::Boolean),
            Token::of(TokenType::Null),
            Token::of(TokenType::Expression, U"break"),
            Token::of(TokenType::Expression, U"continue"),
            Token::of(TokenType::Expression, U"return"),
            Token::of(TokenType::Operator, U"++"),
            Token::of(TokenType::Operator, U"--"),
            Token::of(TokenType::Close),
            Token::of(TokenType::Stop),
            Token::of(TokenType::End),
        };

        /**
         * The array of tokens forbidden after the new line for the semicolon the be inserted.
         */
        const Token FORBIDDEN_AFTER[14] = {
            Token::of(TokenType::Operator, U"="),
            Token::of(TokenType::Operator, U"+"),
            Token::of(TokenType::Operator, U"-"),
            Token::of(TokenType::Operator, U"*"),
            Token::of(TokenType::Operator, U"/"),
            Token::of(TokenType::Operator, U"<"),
            Token::of(TokenType::Operator, U">"),
            Token::of(TokenType::Operator, U"?"),
            Token::of(TokenType::Operator, U"!"),
            Token::of(TokenType::Operator, U"^"),
            Token::of(TokenType::Operator, U"&"),
            Token::of(TokenType::Operator, U"~"),
            Token::of(TokenType::Operator, U"$"),
            Token::of(TokenType::Operator, U"."),
        };

    private:
        /**
         * The list of the input tokens.
         */
        List<Token> tokens;

        /**
         * The index of the currently parsed token.
         */
        uint cursor = 0;

        /**
         * The currently parsed token.
         */
        Token token = Token::of(TokenType::None);

        /**
         * The previously parsed token.
         */
        Token lastToken = Token::of(TokenType::None);

        /**
         * The next parsed token.
         */
        Token nextToken = Token::of(TokenType::None);

    public:
        /**
         * Initialize the transformer
         * @param tokens input tokens
         */
        Transformer(List<Token> tokens);
    
        /**
         * Apply the transformer on the tokens.
         * @return token list with inserted semicolons
         */
        List<Token> transform();

    private:
        /**
         * Update the currently parsed tokens.
         */
        void update();

        /**
         * Check if two tokens are equals. Ignore value checking for certain token types.
         * @param left first token to check
         * @param right second token to check
         * @return true if the two tokens are equals
         */
        bool equals(Token left, Token right);

        /**
         * Safely get the token at the given index.
         * @return token at the given index
         */
        Token safeGet(uint index);

        /**
         * Determine if there are more tokens to be parsed.
         * @return true if there are more tokens
         */
        bool hasNext();
    };
}