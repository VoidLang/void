#include "MethodNode.hpp"

namespace Compiler {
    MethodNode::MethodNode()
        : Node(NodeType::Method)
    { }

    Parameter::Parameter(Token type, List<Token> generics, bool varargs, UString name) 
        : type(type), generics(generics), varargs(varargs), name(name)
    { }

    ReturnType::ReturnType(Token type, List<Token> generics, Option<UString> name)
        : type(type), generics(generics), name(name)
    { }
}