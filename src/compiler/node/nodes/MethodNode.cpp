#include "MethodNode.hpp"

namespace Compiler {
    MethodNode::MethodNode(List<UString> modifiers, List<ReturnType> returnTypes, UString name, List<Parameter> parameters, List<Node> body)
        : Node(NodeType::Method), modifiers(modifiers), returnTypes(returnTypes), name(name), parameters(parameters), body(body)
    { }

    Parameter::Parameter(Token type, List<Token> generics, bool varargs, UString name) 
        : type(type), generics(generics), varargs(varargs), name(name)
    { }

    ReturnType::ReturnType(Token type, List<Token> generics, Option<UString> name)
        : type(type), generics(generics), name(name)
    { }
}