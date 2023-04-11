#pragma once

#include "../../../Common.hpp"
#include "../../token/Token.hpp"
#include "../Node.hpp"

namespace Compiler {
    class LocalDeclare : public Modifiable {
    public:
        Token type;

        List<Token> generics;

        UString name;

        LocalDeclare(Token type, List<Token> generics, UString name);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class MultiLocalDeclare : public Modifiable {
    public:
        Token type;

        List<Token> generics;

        TreeMap<UString, Option<Node*>> locals;
    
        MultiLocalDeclare(Token type, List<Token> generics, TreeMap<UString, Option<Node*>> locals);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class LocalDeclareAssign : public Modifiable {
    public:
        Token type;

        List<Token> generics;

        UString name;

        Node* value;

        LocalDeclareAssign(Token type, List<Token> generics, UString name, Node* value);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    
    class LocalDeclareDestructure : public Node {
    public:
        List<UString> members;

        Node* value;

        LocalDeclareDestructure(List<UString> members, Node* value);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    
    class LocalAssign : public Node {
    public:
        UString name;

        Node* value;

        LocalAssign(UString name, Node* value);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };   
}