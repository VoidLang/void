#include "TypeNode.hpp"

namespace Compiler {
    TypeNode::TypeNode(NodeType type, List<UString> modifiers, UString name, List<UString> genericNames)
        : Node(type), modifiers(modifiers), name(name), genericNames(genericNames)
    { }

    Class::Class(List<UString> modifiers, UString name, List<UString> genericNames, List<Node*> body)
        : TypeNode(NodeType::Class, modifiers, name, genericNames), body(body)
    { }

    TupleStruct::TupleStruct(List<UString> modifiers, UString name, List<UString> genericNames, bool typed, List<Parameter> parameters) 
        : TypeNode(NodeType::TupleStruct, modifiers, name, genericNames), typed(typed), parameters(parameters)
    { }
}
