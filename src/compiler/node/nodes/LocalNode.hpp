#pragma once

#include "../../../Common.hpp"
#include "../../token/Token.hpp"
#include "../Node.hpp"

namespace Compiler {
    class LocalNode : public Node {
    public:
        Token type;

        UString name;

        Option<Node> value;

        LocalNode(Token type, UString name, Option<Node> value);

        /**
         * Debug the content of the parsed node.
         */
        void debug() override;

        /**
         * Debug the content of the parsed node.
         */
        void debug2();
    };
}