#include "LocalNode.hpp"

namespace Compiler {
    LocalNode::LocalNode(Token type, UString name, Option<Node> value)
        : Node(NodeType::Local), type(type), name(name), value(value)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void LocalNode::debug() {
        print("LocalNode{type=" << type << ", name=" << name);
        if (value.has_value()) {
            print(", value=");
            (*value).debug();
        }
        print("}");
    }

    /**
     * Debug the content of the parsed node.
     */
    void LocalNode::debug2() {
        print("LocalNode{type=" << type << ", name=" << name);
        if (value.has_value()) {
            print(", value=");
            (*value).debug();
        }
        print("}");
    }
}