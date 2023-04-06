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
        void debug() override;
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
        void debug() override;
    };
}