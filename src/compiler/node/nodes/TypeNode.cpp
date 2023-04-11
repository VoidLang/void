#include "TypeNode.hpp"

namespace Compiler {
    TypeNode::TypeNode(NodeType type, List<UString> modifiers, UString name, List<UString> genericNames)
        : Node(type), modifiers(modifiers), name(name), genericNames(genericNames)
    { }

    Class::Class(List<UString> modifiers, UString name, List<UString> genericNames, List<Node*> body)
        : TypeNode(NodeType::Class, modifiers, name, genericNames), body(body)
    { }

    TupleParameter::TupleParameter(Token type, List<Token> generics, int dimensions, UString name) 
        : type(type), generics(generics), dimensions(dimensions), name(name)
    { }

    TupleStruct::TupleStruct(List<UString> modifiers, UString name, List<UString> genericNames, bool named, List<TupleParameter> parameters) 
        : TypeNode(NodeType::TupleStruct, modifiers, name, genericNames), named(named), parameters(parameters)
    { }
}
