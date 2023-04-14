#pragma once

#include "../../../Common.hpp"
#include "../Node.hpp"

namespace Compiler {
    class PackageSet : public Node {
    public:
        UString name;

        PackageSet(UString name);
    };

    class Import : public Node {
    public:
        UString package;

        Import(UString package);
    };
}