#pragma once

#include "../../../Common.hpp"
#include "../../token/Token.hpp"
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

    class MethodNode : public Node {
    public:
        List<UString> modifiers;

        List<ReturnType> returnTypes;

        MethodNode();
    };
}