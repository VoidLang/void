#include "ControlFlow.hpp"

#include "../../../util/Strings.hpp"

using namespace Void;

namespace Compiler {
    Return::Return(Package* package, Node* value)
        : Node(NodeType::Return, package), value(value)
    { }

    Return::Return(Package* package)
        : Node(NodeType::Return, package)
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

    Defer::Defer(Package* package, Node* instruction)
        : Node(NodeType::Defer, package), instruction(instruction)
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

    If::If(Package* package, Node* condition, List<Node*> body)
        : Node(NodeType::If, package), condition(condition), body(body)
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

        for (auto elseIf : elseIfs) {
            print(Strings::fill(index + 1, "    "));
            elseIf->debug(index);
        }

        if (elseCase != nullptr) {
            print(Strings::fill(index + 1, "    "));
            elseCase->debug(index);
        }
    }


    ElseIf::ElseIf(Package* package, Node* condition, List<Node*> body)
        : Node(NodeType::ElseIf, package), condition(condition), body(body)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void ElseIf::debug(uint& index) {
        index++;
        println("ElseIf {");

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

    Else::Else(Package* package, List<Node*> body)
        : Node(NodeType::Else, package), body(body)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void Else::debug(uint& index) {
        index++;
        println("Else {");

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

    While::While(Package* package, Node* condition, List<Node*> body)
        : Node(NodeType::While, package), condition(condition), body(body)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void While::debug(uint& index) {
        index++;
        println("While {");

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

    DoWhile::DoWhile(Package* package, List<Node*> body, Node* condition)
        : Node(NodeType::DoWhile, package), body(body), condition(condition)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void DoWhile::debug(uint& index) {
        index++;
        println("DoWhile {");

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

        print(Strings::fill(index + 1, "    ") << "condition: ");
        condition->debug(index);
        if (condition->type == NodeType::Value || condition->type == NodeType::Template)
            println("");

        println(Strings::fill(index, "    ") << "}");
        index--;
    }
}