#include "ValueNode.hpp"

namespace Compiler {
    /**
     * Initialize the single value node.
     * @param value node value
     */
    Value::Value(Token value)
        : Node(NodeType::SingleValue), value(value)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void Value::debug() {
        // print("Value{value=" << value << "}");
        print(value);
    }

    /**
     * Build bytecode for this node.
     * @param bytecode result bytecode list
     */
    void Value::build(List<String>& bytecode) {

    }

    /**
     * Initialize the operation.
     * @param left first expression
     * @param target target operator
     * @param right second expression
     */
    Operation::Operation(Node* left, UString target, Node* right)
        : Node(NodeType::Operation), left(left), target(target), right(right)
    { }

    /**
     * Build bytecode for this node.
     * @param bytecode result bytecode list
     */
    void Operation::build(List<String>& bytecode) {
    }

    /**
     * Debug the content of the parsed node.
     */
    void Operation::debug() {
        print("Operation{left=");
        left->debug();
        print(", operator='" << target << "', right=");
        right->debug();
        print("}");
    }

    Group::Group(Node* value) 
        : Node(NodeType::Group), value(value)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void Group::debug() {
        print("Group{value=");
        value->debug();
        print("}");
    }

    /**
     * Build bytecode for this node.
     * @param bytecode result bytecode list
     */
    void Group::build(List<String>& bytecode) {

    }

    Template::Template(Token value)
        : Node(NodeType::Template), value(value)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void Template::debug() {
        print("Template{value=" << value << "}");
    }

    IndexFetch::IndexFetch(UString name, Node* index)
        : Node(NodeType::IndexFetch), name(name), index(index)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void IndexFetch::debug() {
        print("IndexFetch{name=" << name << ", index=");
        index->debug();
        print("}");
    }

    IndexAssign::IndexAssign(UString name, Node* index, Node* value)
        : Node(NodeType::IndexAssign), name(name), index(index), value(value)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void IndexAssign::debug() {
        print("IndexAssign{name=" << name << ", index=");
        index->debug();
        print(", value=");
        value->debug();
        print("}");
        
    }
}