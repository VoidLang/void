#pragma once

#include "../../../Common.hpp"
#include "../Node.hpp"

namespace Compiler {
    class Return : public Node {
    public:
        Option<Node*> value;

        Return(Node* value);

        Return();

        /**
         * Debug the content of the parsed node.
         */
        void debug() override;
    };
}