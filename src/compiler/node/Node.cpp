#include "Node.hpp"

namespace Compiler {
    OutputStream& operator<<(OutputStream& stream, NodeType& type) {
        static const char* const NAMES[] = {
            "ModifierList",
            "ModifierBlock",
            "Method",
            "Field",
            "MultiField",
            "Package",
            "Import",
            "Class",
            "Struct",
            "TupleStruct",
            "Enum",
            "Interface",
            "Annotation",
            "LocalDeclare",
            "LocalDeclareAssign",
            "LocalDeclareDestruct",
            "LocalAssign",
            "Value",
            "New",
            "Initializator",
            "Operation",
            "SideOperation",
            "MethodCall",
            "Group",
            "Template",
            "Lambda",
            "IndexFetch",
            "IndexAssign",
            "Return",
            "Defer",
            "Tuple",
            "If",
            "ElseIf",
            "Else",
            "While",
            "DoWhile",
            "For",
            "ForEach",
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
        println("Not implemented (" << type << ")");
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
    { exit(501); } // TODO handle exception instead of panicing

    /**
     * Debug the content of the parsed node.
     */
    void ErrorNode::debug(uint& index) {
        println("Error");
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
        println("Finish");
    }

    Modifiable::Modifiable(NodeType type) 
        : Node(type)
    { }
}