#include "MethodNode.hpp"

#include "../../../util/Strings.hpp"
using namespace Void;

namespace Compiler {
    MethodNode::MethodNode(List<ReturnType> returnTypes, UString name, List<Parameter> parameters, List<Node*> body)
        : Modifiable(NodeType::Method), returnTypes(returnTypes), name(name), parameters(parameters), body(body)
    { }

    /**
     * Build bytecode for this node.
     * @param bytecode result bytecode list
     */
    void MethodNode::build(List<UString>& bytecode) {
        bytecode.push_back(U"    mdef " + name);
        if (!modifiers.empty())
            bytecode.push_back(U"    mmod " + Strings::join(modifiers, U" "));
        // TODO make an universal type parser for parameters & return type
        if (!parameters.empty()) {
            UString params;
            for (uint i = 0; i < parameters.size(); i++) {
                params += parameters[i].type.value;
                if (i < parameters.size() - 1)
                    params += U" ";
            }
            bytecode.push_back(U"    mparam " + params);
        }
        bytecode.push_back(U"    mreturn " + parseReturnType());
        bytecode.push_back(U"    mbegin");
        bytecode.push_back(U"    mend");
    }

    /**
     * Parse the return type of the method.
     */
    UString MethodNode::parseReturnType() {
        // TODO handle tuple return type
        if (returnTypes.size() > 1)
            // TODO return void for now
            return U"V";

        Token type = returnTypes[0].type;
        UString value = type.value;
        if (value == U"void")
            return U"V";
        else if (value == U"byte")
            return U"B";
        else if (value == U"short")
            return U"S";
        else if (value == U"int")
            return U"I";
        else if (value == U"long")
            return U"J";
        else if (value == U"float")
            return U"F";
        else if (value == U"double")
            return U"D";
        else if (value == U"bool")
            return U"Z";
        // TODO try to resolve identifier type
        else
            error("Unknown return type: '" << type << "'.");
            
        return U"V";
    }

    Parameter::Parameter(Token type, List<Token> generics, bool varargs, UString name)
        : type(type), generics(generics), varargs(varargs), name(name)
    { }

    ReturnType::ReturnType(Token type, List<Token> generics, Option<UString> name)
        : type(type), generics(generics), name(name)
    { }

    MethodCall::MethodCall(UString name, List<Node*> arguments)
        : Node(NodeType::MethodCall), name(name), arguments(arguments)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void MethodCall::debug(uint& index) {
        index++;
        println("MethodCall {");

        println(Strings::fill(index + 1, "    ") << "name: " << name);

        println(Strings::fill(index + 1, "    ") << "arguments: [");
        for (auto arg : arguments) {
            print(Strings::fill(index + 2, "    "));
            index++;
            arg->debug(index);
            index--;
            if (arg->type == NodeType::Value || arg->type == NodeType::Template)
                println("");
        }
        println(Strings::fill(index + 1, "    ") << "]");
        
        println(Strings::fill(index, "    ") << "}");
        index--;
    }

    Lambda::Lambda(bool typed, List<Parameter> parameters, List<Node*> body)
        : Node(NodeType::Lambda), typed(typed), parameters(parameters), body(body)
    { }

    /**
     * Debug the content of the parsed node.
     */
    void Lambda::debug(uint& index) {
        index++;
        println("Lambda {");

        println(Strings::fill(index + 1, "    ") << "typed: " << (typed ? "true" : "false"));

        println(Strings::fill(index + 1, "    ") << "parameters: [");

        for (auto param : parameters) {
            print(Strings::fill(index + 2, "    "));
            if (typed) {
                print(param.type);
                if (param.varargs)
                    print("...");
                print(" ");
            }
            print(param.name);
            println("");
        }

        println(Strings::fill(index + 1, "    ") << "]");

        println(Strings::fill(index + 1, "    ") << "body: {");
        for (auto element : body) {
            print(Strings::fill(index + 2, "    "));
            index++;
            element->debug(index);
            if (element->type == NodeType::Value || element->type == NodeType::Template)
                println("");
            index--;
        }
        println(Strings::fill(index + 1, "    ") << "}");

        println(Strings::fill(index, "    ") << "}");
        index--;
    }
}