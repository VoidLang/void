#include "NodeParser.hpp"

namespace Compiler {
    /**
     * Initialize the token parser.
     */
    NodeParser::NodeParser(List<Token> tokens)
        : tokens(tokens)
    { }

    /**
     * Parse the next instruction node.
     * @return new instruction node
     */
    Node NodeParser::next() {
        return {};
    }

    /**
     * Get the current at the index.
     * @return currently parsed token
     */
    Token NodeParser::peek() {
        return at(cursor);
    }

    /**
     * Get the token at the current index and move to the next position.
     * @return currently parsed token
     */
    Token NodeParser::get() {
        return at(cursor++);
    }

    /**
     * Move the cursor with the give amount.
     * @param amount cursor move amount
     */
    void NodeParser::skip(uint amount) {
        cursor += amount;
    }

    /**
     * Get the token at the given index.
     * @param index token data index
     * @return otken at the index or null if not in bounds
     */
    Token NodeParser::at(uint index) {
        return has(index) ? tokens[index] : Token::of(TokenType::Finish);
    }

    /**
     * Determine if the given index is in bounds of the data size.
     * @param index target index to check
     * @return true if hte index is in bounds
     */
    bool NodeParser::has(uint index) {
        return index >= 0 && index < tokens.size();
    }
}