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
            print("value=");
            (*value)->debug();
        }
        print("}");
    }
}