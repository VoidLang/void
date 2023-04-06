#include "Node.hpp"

namespace Compiler {
    OutputStream& operator<<(OutputStream& stream, NodeType& type) {
        static const char* const NAMES[] = {
            "Method",
            "Package",
            "Import",
            "Type",
            "LocalDeclare",
            "LocalDeclareAssign",
            "LocalAssign",
            "SingleValue",
            "Operation",
            "MethodCall",
            "Group",
            "Error",
            "Finish"
        };
        return stream << NAMES[static_cast<int>(type)];
    }

    /**
     * Initialize the node.
     * @param type node type
     */
    Node::Node(NodeType type)
        : type(type)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void Node::debug() {
        print("Not implemented (" << type << ")");
    }

    /**
     * Build bytecode for this node.
     * @param bytecode result bytecode list
     */
    void Node::build(List<String>& bytecode) {
        println("Building not implemented for " << type);
    }

    /**
     * Initialize the error node.
     */
    ErrorNode::ErrorNode()
        : Node(NodeType::Error)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void ErrorNode::debug() {
        print("Error");
    }

    /**
     * Initialize the finish node.
     */
    FinishNode::FinishNode()
        : Node(NodeType::Finish)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void FinishNode::debug() {
        print("Finish");
    }
}