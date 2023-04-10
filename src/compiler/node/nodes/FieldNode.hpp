#pragma once

#include "../Node.hpp"
#include "../../token/Token.hpp"

namespace Compiler {
    class FieldNode {
        List<UString> modifiers;

        Token type;

        List<Token> generics;

        UString name;

        Option<Node*> value;
    };
}