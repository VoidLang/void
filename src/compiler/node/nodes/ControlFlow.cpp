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
        index++;
        println("Defer {");

        print(Strings::fill(index + 1, "    "));
        instruction->debug(index);
        if (instruction->type == NodeType::Value || instruction->type == NodeType::Template)
            println("");

        println(Strings::fill(index, "    ") << "}");
        index--;
    }

    If::If(Node* condition, List<Node*> body)
        : Node(NodeType::If), condition(condition), body(body)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void If::debug(uint& index) {
        index++;
        println("If {");

        print(Strings::fill(index + 1, "    ") << "condition: ");
        condition->debug(index);
        if (condition->type == NodeType::Value || condition->type == NodeType::Template)
            println("");

        println(Strings::fill(index + 1, "    ") << "body: {");
        for (uint i = 0; i < body.size(); i++) {
            print(Strings::fill(index + 2, "    "));
            auto element = body[i];
            index++;
            element->debug(index);
            index--;
            if (element->type == NodeType::Value || element->type == NodeType::Template)
                println("");
        }
        println(Strings::fill(index + 1, "    ") << "}");

        println(Strings::fill(index, "    ") << "}");
        index--;
    }
}