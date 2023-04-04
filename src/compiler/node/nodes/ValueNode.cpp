#include "ValueNode.hpp"

namespace Compiler {
    /**
     * Initialize the single value node.
     * @param value node value
     */
    SingleValue::SingleValue(Token value) 
        : Node(NodeType::SingleValue), value(value)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void SingleValue::debug() {
        print("SingleValue{value=" << value << "}");
    }

    /**
     * Initialize the operation.
     * @param left first expression
     * @param target target operator
     * @param right second expression
     */
    Operation::Operation(Node left, UString target, Node right)
        : Node(NodeType::Operation), left(left), target(target), right(right)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void Operation::debug() {
        print("Operation{left=");
        left.debug();
        print(", operator=" << target);
        right.debug();
        print("}");
    }
}