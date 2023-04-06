#pragma once

#include "../../../Common.hpp"
#include "../../token/Token.hpp"
#include "../Node.hpp"

namespace Compiler {
    /**
     * Represents a node that holds a single value.
     */
    class Value : public Node {
    public:
        /**
         * The held value of the node.
         */
        Token value;

        /**
         * Initialize the single value node.
         * @param value node value
         */
        Value(Token value);

        /**
         * Debug the content of the parsed node.
         */
        void debug() override;
    };

    /**
     * Represents an instruction that performs an operation on two expressions.
     */
    class Operation : public Node {
    public:
        /**
         * The first expression of the operation.
         */
        Node* left;

        /**
         * The target operator of the operation.
         */
        UString target;
        
        /**
         * The second expression of the operation.
         */
        Node* right;

        /**
         * Initialize the operation.
         * @param left first expression
         * @param target target operator
         * @param right second expression
         */
        Operation(Node* left, UString target, Node* right);

        /**
         * Debug the content of the parsed node.
         */
        void debug() override;
    };
}