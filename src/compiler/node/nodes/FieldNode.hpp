#pragma once

#include "../Node.hpp"
#include "../../token/Token.hpp"

namespace Compiler {
    class FieldNode : public Modifiable {
    public:
        Token type;

        List<Token> generics;

        UString name;

        Option<Node*> value;
    
        FieldNode(Token type, List<Token> generics, UString name, Option<Node*> value);
    };

    class MultiField : public Modifiable {
    public:
        Token type;
        
        List<Token> generics;

        TreeMap<UString, Option<Node*>> fields;

        MultiField(Token type, List<Token> generics, TreeMap<UString, Option<Node*>> fields);
    };
}