#pragma once

#include "../../Common.hpp"
#include "../token/Token.hpp"
#include "Node.hpp"

namespace Compiler {
    /**
     * Represents a parser that transforms raw tokens to instructions.
     */
    class NodeParser {
    private:
        /**
         * The list of the tokens to be parsed.
         */
        List<Token> tokens;

        /**
         * The index of the currently parsed token.
         */
        uint cursor = 0;

        /**
         * Initialize the token parser.
         */
        NodeParser(List<Token> tokens);

    public:
        /**
         * Parse the next instruction node.
         * @return new instruction node
         */
        Node next();

        /**
         * Get the current at the index.
         * @return currently parsed token
         */
        Token peek();

        /**
         * Get the token at the current index and move to the next position.
         * @return currently parsed token
         */
        Token get();

        /**
         * Move the cursor with the give amount.
         * @param amount cursor move amount
         */
        void skip(uint amount);

        /**
         * Get the token at the given index.
         * @param index token data index
         * @return otken at the index or null if not in bounds
         */
        Token at(uint index);

        /**
         * Determine if the given index is in bounds of the data size.
         * @param index target index to check
         * @return true if hte index is in bounds
         */
        bool has(uint index);
    };
}