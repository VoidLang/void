#include "MethodNode.hpp"

#include "../../../util/Strings.hpp"
using namespace Void;

namespace Compiler {
    MethodNode::MethodNode(List<UString> modifiers, List<ReturnType> returnTypes, UString name, List<Parameter> parameters, List<Node*> body)
        : Node(NodeType::Method), modifiers(modifiers), returnTypes(returnTypes), name(name), parameters(parameters), body(body)
    { }

    Parameter::Parameter(Token type, List<Token> generics, bool varargs, UString name)
        : type(type), generics(generics), varargs(varargs), name(name)
    { }

    ReturnType::ReturnType(Token type, List<Token> generics, Option<UString> name)
        : type(type), generics(generics), name(name)
    { }

    MethodCall::MethodCall(UString name, List<Node*> arguments)
        : Node(NodeType::MethodCall), name(name), arguments(arguments)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void MethodCall::debug(uint& index) {
        index++;
        println("MethodCall {");

        println(Strings::fill(index + 1, "    ") << "name: " << name);

        println(Strings::fill(index + 1, "    ") << "arguments: [");
        for (auto arg : arguments) {
            print(Strings::fill(index + 2, "    "));
            index++;
            arg->debug(index);
            index--;
            if (arg->type == NodeType::Value || arg->type == NodeType::Template)
                println("");
        }
        println(Strings::fill(index + 1, "    ") << "]");
        
        println(Strings::fill(index, "    ") << "}");
        index--;
    }

    Lambda::Lambda(bool typed, List<Parameter> parameters, List<Node*> body)
        : Node(NodeType::Lambda), typed(typed), parameters(parameters), body(body)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void Lambda::debug(uint& index) {
        index++;
        println("Lambda {");

        println(Strings::fill(index + 1, "    ") << "typed: " << (typed ? "true" : "false"));

        println(Strings::fill(index + 1, "    ") << "parameters: [");

        for (auto param : parameters) {
            print(Strings::fill(index + 2, "    "));
            if (typed) {
                print(param.type);
                if (param.varargs)
                    print("...");
                print(" ");
            }
            print(param.name);
            println("");
        }

        println(Strings::fill(index + 1, "    ") << "]");

        println(Strings::fill(index + 1, "    ") << "body: {");
        for (auto element : body) {
            print(Strings::fill(index + 2, "    "));
            index++;
            element->debug(index);
            if (element->type == NodeType::Value || element->type == NodeType::Template)
                println("");
            index--;
        }
        println(Strings::fill(index + 1, "    ") << "}");

        println(Strings::fill(index, "    ") << "}");
        index--;
    }
}