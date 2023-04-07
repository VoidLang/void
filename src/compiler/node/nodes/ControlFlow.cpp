#include "ControlFlow.hpp"

#include "../../../util/Strings.hpp"

using namespace Void;

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
    void Return::debug(uint& index) {
        index++;
        println("Return {");

        if (value.has_value()) {
            print(Strings::fill(index + 1, "    "));
            (*value)->debug(index);
            if ((*value)->type == NodeType::Value || (*value)->type == NodeType::Template)
                println("");
        }

        println(Strings::fill(index, "    ") << "}");
        index--;
    }

    Defer::Defer(Node* instruction)
        : Node(NodeType::Defer), instruction(instruction)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void Defer::debug(uint& index) {
        print("Defer{");
        instruction->debug(index);
        print("}");
    }
}