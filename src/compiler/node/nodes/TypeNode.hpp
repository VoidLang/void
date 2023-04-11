#pragma once

#include "../../../Common.hpp"
#include "../Node.hpp"
#include "../../token/Token.hpp"

namespace Compiler {
    class ModifierList : public Node {
    public:
        List<UString> modifiers;

        ModifierList(List<UString> modifiers);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class ModifierBlock : public Node {
    public:
        List<UString> modifiers;

        ModifierBlock(List<UString> modifiers);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class TypeNode : public Modifiable {
    public:
        UString name;

        List<UString> genericNames;

        TypeNode(NodeType type, UString name, List<UString> genericNames);
    };

    class Class : public TypeNode {
    public:
        List<Node*> body;

        Class(UString name, List<UString> genericNames, List<Node*> body);
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

        TupleStruct(UString name, List<UString> genericNames, bool named, List<TupleParameter> parameters);
    };

    class Enum : public Node {

    };

    class Interface : public Node {

    };

    class Annotation : public Node {

    };
}