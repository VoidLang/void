#include "ValueNode.hpp"

namespace Compiler {
    /**
     * Initialize the single value node.
     * @param value node value
     */
    Value::Value(Token value)
        : Node(NodeType::SingleValue), value(value)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void Value::debug() {
        print("Value{value=" << value << "}");
    }

    /**
     * Initialize the operation.
     * @param left first expression
     * @param target target operator
     * @param right second expression
     */
    Operation::Operation(Node* left, UString target, Node* right)
        : Node(NodeType::Operation), left(left), target(target), right(right)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void Operation::debug() {
        print("Operation{left=");
        left->debug();
        print(", operator='" << target << "', right=");
        right->debug();
        print("}");
    }
}