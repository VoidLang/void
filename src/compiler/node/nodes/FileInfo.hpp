#pragma once

#include "../../../Common.hpp"
#include "../Node.hpp"

namespace Compiler {
    class Package : public Node {
    public:
        UString name;

        Package(UString name);
    };

    class Import : public Node {
    public:
        UString package;

        Import(UString package);
    };
}