#include "ControlFlow.hpp"

namespace Compiler {
    Return::Return(Node* value)
        : Node(NodeType::Return), value(value)
    { }

    Return::Return()
        : Node(NodeType::Return)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void Return::debug() {
        print("Return{");
        if (value.has_value()) {
            (*value)->debug();
        }
        print("}");
    }

    Defer::Defer(Node* instruction)
        : Node(NodeType::Defer), instruction(instruction)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void Defer::debug() {
        print("Defer{");
        instruction->debug();
        print("}");
    }
}