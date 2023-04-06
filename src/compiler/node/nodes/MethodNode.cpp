#include "MethodNode.hpp"

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
    void MethodCall::debug() {
        print("MethodCall{name=" << name);
        print(", arguments=[");
        for (uint i = 0; i < arguments.size(); i++) {
            arguments[i]->debug();
            if (i < arguments.size() - 1)
                print(", ");
        }
        print("]}");
    }
}