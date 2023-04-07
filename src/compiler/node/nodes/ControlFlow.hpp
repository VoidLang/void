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
        void debug(uint& index) override;
    };

    class Defer : public Node {
    public:
        Node* instruction;

        Defer(Node* instruction);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class ElseIf : public Node {
    public:
        Node* condition;

        List<Node*> body;

        ElseIf(Node* condition, List<Node*> body);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class Else : public Node {
    public:
        List<Node*> body;

        Else(List<Node*> body);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class If : public Node {
    public:
        Node* condition;

        List<Node*> body;

        List<ElseIf*> elseIfs;

        Else* elseCase;

        If(Node* condition, List<Node*> body);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };
}