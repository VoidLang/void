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
    void LocalDeclare::debug(uint& index) {
        print("LocalDeclare{type=" << type << ", name=" << name << "}");
    }


    LocalDeclareAssign::LocalDeclareAssign(Token type, UString name, Node* value)
        : Node(NodeType::LocalDeclareAssign), type(type), name(name), value(value)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void LocalDeclareAssign::debug(uint& index) {
        index++;
        println("LocalDeclareAssign {");

        println(Strings::fill(index + 1, "    ") << "type: " << type);

        println(Strings::fill(index + 1, "    ") << "name: " << name);

        print(Strings::fill(index + 1, "    ") << "value: ");
        value->debug(index);
        if (value->type == NodeType::Value || value->type == NodeType::Template)
            println("");

        println(Strings::fill(index, "    ") << "}");
        index--;
    }

    LocalDeclareDestruct::LocalDeclareDestruct(List<UString> members, Node* value)
        : Node(NodeType::LocalDeclare), members(members), value(value)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void LocalDeclareDestruct::debug(uint& index) {
        index++;
        println("LocalDeclareDestruct {");

        println(Strings::fill(index + 1, "    ") << "members: " << Strings::join(members, U", "));

        print(Strings::fill(index + 1, "    ") << "value: ");
        value->debug(index);
        if (value->type == NodeType::Value || value->type == NodeType::Template)
            println("");

        println(Strings::fill(index, "    ") << "}");
        index--;
    }


    LocalAssign::LocalAssign(UString name, Node* value) 
        : Node(NodeType::LocalAssign), name(name), value(value)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void LocalAssign::debug(uint& index) {
        index++;
        println("LocalAssign {");

        println(Strings::fill(index + 1, "    ") << "name: " << name);

        print(Strings::fill(index + 1, "    ") << "value: ");
        value->debug(index);
        if (value->type == NodeType::Value || value->type == NodeType::Template)
            println("");

        println(Strings::fill(index, "    ") << "}");
        index--;
    }
}