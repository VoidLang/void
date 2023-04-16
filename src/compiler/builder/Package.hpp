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

#include "Application.hpp"

namespace Compiler {
    class Application;
    class MethodNode;
    class Class;
    class NormalStruct;
    class TupleStruct;
    class TypeNode;
    class MethodNode;
    class Parameter;

    /**
     * Represens a per-file package. Each source file is a package as well. If the package is 
     * explicitly set, the content of it is accessible from other packages as well.
     */
    class Package {
    public:
        /**
         * The target application of the whole program.
         */
        Application* application;

        /**
         * The name of the package.
         */
        // TODO make the package name something invalid by default, therefore
        // if the source file does not set the package, name, an other package
        // will not be able to resolve the content of this package
        UString name = createAnonymusName(U"package");

        /**
         * Determine if the package has a name specified.
         */
        bool named = false;

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

        /**
         * Initialize the package.
         * @param application parent application
         */
        Package(Application* application);

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
         * Try to resolve a declared type from the package.
         * @param type target type name
         * @return fully qualified type, or empty string if not found
         */
        UString resolveType(Token type);

        /**
         * Create an anonymus name for the given type specifier.
         * @param prefix type specifier prefix
         */
        static UString createAnonymusName(UString prefix);
    };
}
