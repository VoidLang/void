#include "LocalNode.hpp"

#include "../../../util/Strings.hpp"

using namespace Void;

namespace Compiler {
    LocalDeclare::LocalDeclare(Token type, UString name)
        : Node(NodeType::LocalDeclare), type(type), name(name)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void LocalDeclare::debug() {
        print("LocalDeclare{type=" << type << ", name=" << name << "}");
    }


    LocalDeclareAssign::LocalDeclareAssign(Token type, UString name, Node* value)
        : Node(NodeType::LocalDeclareAssign), type(type), name(name), value(value)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void LocalDeclareAssign::debug() {
        print("LocalDeclareAssign{type=" << type << ", name=" << name << ", value=");
        value->debug();
        print("}");
    }

    LocalDeclareDestruct::LocalDeclareDestruct(List<UString> members, Node* value)
        : Node(NodeType::LocalDeclare), members(members), value(value)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void LocalDeclareDestruct::debug() {
        print("LocalDeclareDestruct{members=[" << Strings::join(members, U", ") << "], value=");
        value->debug();
        print("}");
    }


    LocalAssign::LocalAssign(UString name, Node* value) 
        : Node(NodeType::LocalAssign), name(name), value(value)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void LocalAssign::debug() {
        print("LocalAssign{name=" << name << ", value=");
        value->debug();
        print("}");
    }
}