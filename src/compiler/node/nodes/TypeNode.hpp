#pragma once

#include "../../../Common.hpp"
#include "../Node.hpp"

namespace Compiler {
    class TypeNode : public Node {
    public:
        TypeNode(NodeType type);
    };

    class Class : public Node {

    };

    class Struct : public Node {

    };

    class TupleStruct : public Node {

    };

    class Enum : public Node {

    };

    class Interface : public Node {

    };

    class Annotation : public Node {

    };
}