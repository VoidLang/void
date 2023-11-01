#include "FieldNode.hpp"

namespace Compiler {
    FieldNode::FieldNode(Package* package, Token type, List<Token> generics, UString name, Option<Node*> value)
        : Modifiable(NodeType::Field, package), type(type), generics(generics), name(name), value(value)
    { }

    MultiField::MultiField(Package* package, Token type, List<Token> generics, TreeMap<UString, Option<Node*>> fields)
        : Modifiable(NodeType::MultiField, package), type(type), generics(generics), fields(fields)
    { }
}