#pragma once

#include "../../../Common.hpp"
#include "../Node.hpp"
#include "../../token/Token.hpp"

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

    class TupleParameter {
    public:
        Token type;

        List<Token> generics;

        int dimensions;

        UString name;

        TupleParameter(Token type, List<Token> generics, int dimensions, UString name);
    };

    class TupleStruct : public TypeNode {
    public:
        bool named;

        List<TupleParameter> parameters;

        TupleStruct(List<UString> modifiers, UString name, List<UString> genericNames, bool named, List<TupleParameter> parameters);
    };

    class Enum : public Node {

    };

    class Interface : public Node {

    };

    class Annotation : public Node {

    };
}