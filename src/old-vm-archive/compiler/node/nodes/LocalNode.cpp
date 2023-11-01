#include "LocalNode.hpp"

#include "../../../util/Strings.hpp"

using namespace Void;

namespace Compiler {
    LocalDeclare::LocalDeclare(Package* package, Token type, List<Token> generics, UString name)
        : Modifiable(NodeType::LocalDeclare, package), type(type), generics(generics), name(name)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void LocalDeclare::debug(uint& index) {
        index++;
        println("LocalDeclare {");

        println(Strings::fill(index + 1, "    ") << "type: " << type);

        if (!generics.empty()) {
            print(Strings::fill(index + 1, "    ") << "generics: " );
            for (auto gen : generics) 
                print(gen.value);
            println("");
        }

        println(Strings::fill(index + 1, "    ") << "name: " << name);

        println(Strings::fill(index, "    ") << "}");
        index--;
    }

    MultiLocalDeclare::MultiLocalDeclare(Package* package, Token type, List<Token> generics, TreeMap<UString, Option<Node*>> locals)
        : Modifiable(NodeType::MultiLocalDeclare, package), type(type), generics(generics), locals(locals)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void MultiLocalDeclare::debug(uint& index) {
        index++;
        println("MultiLocalDeclare {");

        println(Strings::fill(index + 1, "    ") << "type: " << type);

        if (!generics.empty()) {
            print(Strings::fill(index + 1, "    ") << "generics: ");
            for (auto gen : generics)
                print(gen.value);
            println("");
        }

        println(Strings::fill(index + 1, "    ") << "fields: [");
        for (auto& [key, value] : locals) {
            print(Strings::fill(index + 2, "    ") << key);
            if (value.has_value()) {
                print(": ");
                index++;
                (*value)->debug(index);
                index--;
                if ((*value)->type == NodeType::Value || (*value)->type == NodeType::Template)
                    println("");
            } else {
                println("");
            }
        }
        println(Strings::fill(index + 1, "    ") << "]");

        println(Strings::fill(index, "    ") << "}");
        index--;
    }

    LocalDeclareAssign::LocalDeclareAssign(Package* package, Token type, List<Token> generics, UString name, Node* value)
        : Modifiable(NodeType::LocalDeclareAssign, package), generics(generics), type(type), name(name), value(value)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void LocalDeclareAssign::debug(uint& index) {
        index++;
        println("LocalDeclareAssign {");

        println(Strings::fill(index + 1, "    ") << "type: " << type);

        if (!generics.empty()) {
            print(Strings::fill(index + 1, "    ") << "generics: ");
            for (auto gen : generics)
                print(gen.value);
            println("");
        }

        println(Strings::fill(index + 1, "    ") << "name: " << name);

        print(Strings::fill(index + 1, "    ") << "value: ");
        value->debug(index);
        if (value->type == NodeType::Value || value->type == NodeType::Template)
            println("");

        println(Strings::fill(index, "    ") << "}");
        index--;
    }

    LocalDeclareDestructure::LocalDeclareDestructure(Package* package, List<UString> members, Node* value)
        : Node(NodeType::LocalDeclareDestructure, package), members(members), value(value)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void LocalDeclareDestructure::debug(uint& index) {
        index++;
        println("LocalDeclareDestructure {");

        println(Strings::fill(index + 1, "    ") << "members: " << Strings::join(members, U", "));

        print(Strings::fill(index + 1, "    ") << "value: ");
        value->debug(index);
        if (value->type == NodeType::Value || value->type == NodeType::Template)
            println("");

        println(Strings::fill(index, "    ") << "}");
        index--;
    }


    LocalAssign::LocalAssign(Package* package, UString name, Node* value)
        : Node(NodeType::LocalAssign, package), name(name), value(value)
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