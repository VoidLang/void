#include "Package.hpp"

namespace Compiler {
    /**
     * Get a type from the package by its name.
     * @param name target type name
     * @return found type or nullptr if not found
     */
    TypeNode* Package::getType(UString name) {
        // check if a package class uses the given name
        for (auto& [_, classNode] : classes) {
            if (classNode->name == name)
                return classNode;
        }

        // check if a package struct uses the given name
        for (auto& [_, structNode] : structs) {
            if (structNode->name == name)
                return structNode;
        }

        // check if a package tuple struct uses the given name
        for (auto& [_, tupleStruct] : tupleStructs) {
            if (tupleStruct->name == name)
                return tupleStruct;
        }

        // package type not found, return null type pointer
        return nullptr;
    }

    /**
     * Get a method from the package by its signature.
     * @param name target method name
     * @param parameters target method parameters
     * @return found method or nullptr if not found
     */
    MethodNode* Package::getMethod(UString name, List<Parameter> parameters) {
        // get the length of the required parameters list
        ulong checkLength = parameters.size();
        // loop through the declared package methods
        for (MethodNode* method : methods) {
            // get the length of the method's parameter list
            ulong methodLength = method->parameters.size();
            // ignore the method if the method name or parameters length does not match
            if (method->name != name || methodLength != checkLength)
                continue;
            // check if the method parameters match
            for (ulong i = 0; i < checkLength; i++) {
                // ignore method if the parameter at the 
                // current index does not match
                if (method->parameters[i].type.value != parameters[i].type.value)
                    goto search;
            }
            // method parameters matches, method found
            return method;
        search:;
        }
        // method not found, return a null method pointer
        return nullptr;
    }

    /**
     * Compile the parsed nodes to executable bytecode.
     * @bytecode executable bytecode result
     */
    void Package::compile(List<UString>& bytecode) {
        // compile the package classes
        for (auto& [_, classNode] : classes) {
            // compile the class node to bytecode
            classNode->build(bytecode);
        }

        // return if there are no package methods to be parsed
        if (methods.empty())
            return;

        // create an anonymus class for storing package methods
        bytecode.push_back(U"cdef <package>" + name);
        bytecode.push_back(U"cbegin");

        // compile the package methods
        for (MethodNode* method : methods) {
            // compile the method node to bytevode
            method->build(bytecode);
        }

        bytecode.push_back(U"cend");
    }
}