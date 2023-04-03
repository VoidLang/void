#include "Node.hpp"

namespace Compiler {
    Node::Node(NodeType type)
        : type(type)
    { }

    ErrorNode::ErrorNode()
        : Node(NodeType::Error)
    { }

    FinishNode::FinishNode()
        : Node(NodeType::Finish)
    { }
}