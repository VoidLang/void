#pragma once

#include "../../../Common.hpp"
#include "../Node.hpp"

#include "MethodNode.hpp"

namespace Compiler {
    class TypeNode : public Node {
    public:
        List<UString> modifiers;

        UString name;

        List<UString> genericNames;

        TypeNode(NodeType type, List<UString> modifiers, UString name, List<UString> genericNames);
    };

    class Class : public TypeNode {
    public:
        List<Node*> body;

        Class(List<UString> modifiers, UString name, List<UString> genericNames, List<Node*> body);
    };

    class Struct : public Node {

    };

    class TupleStruct : public TypeNode {
    public:

        bool typed;

        List<Parameter> parameters;

        TupleStruct(List<UString> modifiers, UString name, List<UString> genericNames, bool typed, List<Parameter> parameters);
    };

    class Enum : public Node {

    };

    class Interface : public Node {

    };

    class Annotation : public Node {

    };
}