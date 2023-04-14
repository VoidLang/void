#pragma once

#include "../../Common.hpp"
#include "../node/Node.hpp"

#include "../node/nodes/ControlFlow.hpp"
#include "../node/nodes/FieldNode.hpp"
#include "../node/nodes/FileInfo.hpp"
#include "../node/nodes/LocalNode.hpp"
#include "../node/nodes/MethodNode.hpp"
#include "../node/nodes/TypeNode.hpp"
#include "../node/nodes/ValueNode.hpp"

namespace Compiler {
    /**
     * Represents a per-file parsed node transformer, that converts nodes to actual program parts, such as classes, methods, etc.
     */
    class NodeBuilder {
    private:
        List<Node*> nodes;

        /**
         * The index of the currently parsed node.
         */
        uint cursor = 0;

        /**
         * The name of the package of the file.
         */
        UString package;

        /**
         * The map of the imported packages.
         */
        Map<UString, UString> imports;

        /**
         * The list of the package methods.
         */
        List<MethodNode*> methods;

        /**
         * The map of the package classes.
         */
        Map<UString, Class*> classes;

        /**
         * The map of the package structs.
         */
        Map<UString, NormalStruct*> structs;

        /**
         * The map of the package tuple structs.
         */
        Map<UString, TupleStruct*> tupleStructs;

    public:
        /**
         * Initialize the node builder.
         * @param nodes raw nodes input
         */
        NodeBuilder(List<Node*> nodes);

        /**
         * Build the program from raw parsed tokens.
         */
        void build();

        /**
         * Handle the next package declaration.
         */
        void nextPackage();

        /**
         * Handle the next package method declaration. 
         */
        void nextPackageMethod();

        /**
         * Handle the next package class declaration.
         */
        void nextPackageClass();

        /**
         * Handle the next package struct declaration.
         */
        void nextPackageStruct();

        /**
         * Handle the next pacakge tuple struct declaration.
         */
        void nextPackageTupleStruct();

        /**
         * Check if the given name is already used by a type in the package.
         * @param name type name to check
         */
        void checkTypeNameAvailable(UString name);

        /**
         * Check if the given method signature is already used by a method in the package.
         * @param name method name to check
         * @param parameters method parameters to check
         */
        void checkMethodAvailable(UString name, List<Parameter> parameters);

        /**
         * Get a type from the package by its name.
         * @param name target type name
         * @return found type or nullptr if not found
         */
        TypeNode* getType(UString name);

        /**
         * Get a method from the package by its signature.
         * @param name target method name
         * @param parameters target method parameters
         * @return found method or nullptr if not found
         */
        MethodNode* getMethod(UString name, List<Parameter> parameters);

        /**
         * Compile the parsed nodes to executable bytecode.
         * @bytecode executable bytecode result
         */
        void compile(List<UString>& bytecode);

        /**
         * Get the node at the current index.
         * @return currently parsed token
         */
        Node* peek();

        /**
         * Get the node at the current index.
         * Check if the retrieved token does not match the given type.
         * @param type required token type
         * @return currently parsed token
         */
        Node* peek(NodeType type);

        /**
         * Get the node at the current index.
         * Check if the retrieved token does not match any of the given typs.
         * @param size required token types' length
         * @return currently parsed token
         */
        Node* peek(uint size, ...);

        /**
         * Get the node at the current index and move to the next position.
         * @return currently parsed node
         */
        Node* get();

        /**
         * Get the node at the current index and move to the next position.
         * Check if the retrieved node does not match the given type.
         * @param type required node type
         * @return currently parsed node
         */
        Node* get(NodeType type);

        /**
         * Get the node at the current index and move to the next position.
         * Check if the retrieved node does not match any of the given types.
         * @param size required node types' length
         * @return currently parsed node
         */
        Node* get(uint size, ...);

        /**
         * Move the cursor with the give amount.
         * @param amount cursor move amount
         */
        void skip(uint amount);

        /**
         * Get the node at the given index.
         * @param index node data index
         * @return node at the index or null if not in bounds
         */
        Node* at(uint index);

        /**
         * Determine if the given index is in bounds of the data size.
         * @param index target index to check
         * @return true if the index is in bounds
         */
        bool has(uint index);
    };
}