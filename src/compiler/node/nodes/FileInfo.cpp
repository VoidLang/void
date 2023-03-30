#include "FileInfo.hpp"

namespace Compiler {
    Package::Package(UString name) 
        : Node(NodeType::Package), name(name)
    { }

    Import::Import(UString package)
        : Node(NodeType::Import), package(package)
    { }
}