#include "TypeNode.hpp"

#include "../../../util/Strings.hpp"
using namespace Void;

namespace Compiler {
    ModifierList::ModifierList(Package* package, List<UString> modifiers)
        : Node(NodeType::ModifierList, package), modifiers(modifiers)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void ModifierList::debug(uint& index) {
    }

    ModifierBlock::ModifierBlock(Package* package, List<UString> modifiers)
        : Node(NodeType::ModifierBlock, package), modifiers(modifiers)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void ModifierBlock::debug(uint& index) {
    }

    TypeNode::TypeNode(NodeType type, Package* package, UString name, List<UString> genericNames)
        : Modifiable(type, package), name(name), genericNames(genericNames)
    { }

    /**
     * Get the fully qualified name of the type.
     * @return type name with package and parent
     */
    UString TypeNode::getFullName() {
        UString prefix;
        if (package->named)
            prefix += package->name + U"/";
        if (parent != nullptr)
            prefix += parent->name + U".";
        return prefix + name;
    }

    Class::Class(Package* package, UString name, List<UString> genericNames, List<Node*> body)
        : TypeNode(NodeType::Class, package, name, genericNames), body(body)
    { }

    /**
     * Build bytecode for this node.
     * @param bytecode result bytecode list
     */
    void Class::build(List<UString>& bytecode) {
        bytecode.push_back(U"cdef " + getFullName());
        if (!modifiers.empty()) 
            bytecode.push_back(U"cmod " + Strings::join(modifiers, U" "));
        bytecode.push_back(U"cbegin");

        bytecode.push_back(U"cend");
    }

    NormalStruct::NormalStruct(Package* package, UString name, List<UString> genericNames, List<Node*> body)
        : TypeNode(NodeType::Struct, package, name, genericNames), body(body)
    { }

    TupleParameter::TupleParameter(Token type, List<Token> generics, int dimensions, UString name)
        : type(type), generics(generics), dimensions(dimensions), name(name)
    { }

    TupleStruct::TupleStruct(Package* package, UString name, List<UString> genericNames, bool named, List<TupleParameter> parameters)
        : TypeNode(NodeType::TupleStruct, package, name, genericNames), named(named), parameters(parameters)
    { }
}
