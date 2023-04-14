#pragma once

#include "../../../Common.hpp"
#include "../../token/Token.hpp"
#include "TypeNode.hpp"
#include "../Node.hpp"

namespace Compiler {
    class Parameter {
    public:
        Token type;

        List<Token> generics;

        bool varargs;

        UString name;

        Parameter(Token type, List<Token> generics, bool varargs, UString name);
    };

    class ReturnType {
    public:
        Token type;

        List<Token> generics;

        Option<UString> name;

        ReturnType(Token type, List<Token> generics, Option<UString> name);
    };

    class MethodNode : public Modifiable {
    public:
        List<ReturnType> returnTypes;

        UString name;

        List<Parameter> parameters;

        List<Node*> body;

        UString package = U"";

        TypeNode* parent = nullptr;

        MethodNode(List<ReturnType> returnTypes, UString name, List<Parameter> parameters, List<Node*> body);

        /**
         * Build bytecode for this node.
         * @param bytecode result bytecode list
         */
        void build(List<UString>& bytecode) override;

    private:
        /**
         * Parse the return type of the method.
         */
        UString parseReturnType();
    };

    class MethodCall : public Node {
    public:
        UString name;

        List<Node*> arguments;

        MethodCall(UString name, List<Node*> arguments);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class Lambda : public Node {
    public:
        bool typed;

        List<Parameter> parameters;

        List<Node*> body;

        Lambda(bool typed, List<Parameter> parameters, List<Node*> body);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };
}