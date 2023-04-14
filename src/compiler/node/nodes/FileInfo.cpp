#include "FileInfo.hpp"

namespace Compiler {
    PackageSet::PackageSet(UString name)
        : Node(NodeType::Package), name(name)
    { }

    Import::Import(UString package)
        : Node(NodeType::Import), package(package)
    { }
}