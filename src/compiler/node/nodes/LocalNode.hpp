#pragma once

#include "../../../Common.hpp"
#include "../../token/Token.hpp"
#include "../Node.hpp"

namespace Compiler {
    class LocalDeclare : public Node {
    public:
        Token type;

        UString name;

        LocalDeclare(Token type, UString name);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };


    class LocalDeclareAssign : public Node {
    public:
        Token type;

        UString name;

        Node* value;

        LocalDeclareAssign(Token type, UString name, Node* value);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    
    class LocalDeclareDestruct : public Node {
    public:
        List<UString> members;

        Node* value;

        LocalDeclareDestruct(List<UString> members, Node* value);

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