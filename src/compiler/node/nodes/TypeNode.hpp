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

        UString package = U"";

        TypeNode* parent = nullptr;

        TypeNode(NodeType type, UString name, List<UString> genericNames);

        /**
         * Build bytecode for this node.
         * @param bytecode result bytecode list
         */
        void build(List<UString>& bytecode) override;
    };

    class Class : public TypeNode {
    public:
        List<Node*> body;

        Class(UString name, List<UString> genericNames, List<Node*> body);
    };

    class NormalStruct : public TypeNode {
    public:
        List<Node*> body;

        NormalStruct(UString name, List<UString> genericNames, List<Node*> body);
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