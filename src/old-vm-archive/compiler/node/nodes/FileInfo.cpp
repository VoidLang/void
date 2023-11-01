#include "FileInfo.hpp"

namespace Compiler {
    PackageSet::PackageSet(Package* package, UString name)
        : Node(NodeType::Package, package), name(name)
    { }

    Import::Import(Package* package, UString target)
        : Node(NodeType::Import, package), target(target)
    { }
}