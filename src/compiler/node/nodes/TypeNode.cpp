#include "TypeNode.hpp"

#include "../../../util/Strings.hpp"
using namespace Void;

namespace Compiler {
    ModifierList::ModifierList(List<UString> modifiers)
        : Node(NodeType::ModifierList), modifiers(modifiers)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void ModifierList::debug(uint& index) {
    }

    ModifierBlock::ModifierBlock(List<UString> modifiers) 
        : Node(NodeType::ModifierBlock), modifiers(modifiers)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void ModifierBlock::debug(uint& index) {
    }

    TypeNode::TypeNode(NodeType type, UString name, List<UString> genericNames)
        : Modifiable(type), name(name), genericNames(genericNames)
    { }

    Class::Class(UString name, List<UString> genericNames, List<Node*> body)
        : TypeNode(NodeType::Class, name, genericNames), body(body)
    { }

    TupleParameter::TupleParameter(Token type, List<Token> generics, int dimensions, UString name) 
        : type(type), generics(generics), dimensions(dimensions), name(name)
    { }

    TupleStruct::TupleStruct(UString name, List<UString> genericNames, bool named, List<TupleParameter> parameters) 
        : TypeNode(NodeType::TupleStruct,name, genericNames), named(named), parameters(parameters)
    { }
}
