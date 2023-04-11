#include "FieldNode.hpp"

namespace Compiler {
    FieldNode::FieldNode(Token type, List<Token> generics, UString name, Option<Node*> value)
        : Modifiable(NodeType::Field), type(type), generics(generics), name(name), value(value)
    { }

    MultiField::MultiField(Token type, List<Token> generics, TreeMap<UString, Option<Node*>> fields)
        : Modifiable(NodeType::MultiField), type(type), generics(generics), fields(fields)
    { }
}