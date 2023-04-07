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
            "LocalDeclareDestruct",
            "LocalAssign",
            "Value",
            "Operation",
            "MethodCall",
            "Group",
            "Template",
            "Lambda",
            "IndexFetch",
            "IndexAssign",
            "Return",
            "Defer",
            "Tuple",
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
    void Node::debug(uint& index) {
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
    void ErrorNode::debug(uint& index) {
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
    void FinishNode::debug(uint& index) {
        print("Finish");
    }
}