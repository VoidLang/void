#pragma once

#include "../VirtualMachine.hpp"
#include "Method.hpp"
#include "Field.hpp"

namespace Void {
    class VirtualMachine;
    class Method;
    class Field;

    /**
     * Represens a void class in the virtual machine.
     * Manages methods and static fields.
     * Supports recursive class declaration.
     */
    class Class {
    private:
        /**
         * The running virtual machine.
         */
        VirtualMachine* vm;
        
    public:
        /**
         * The list of the declared class methods.
         */
        List<Method*> methods;

        /**
         * The list of the declared class fields.
         */
        List<Field*> fields;

        /**
         * The name of the class.
         */
        String name;

        /**
         * The superclass of the class.
         */
        String superclass;

        /**
         * The modifiers of the class.
         */
        int modifiers;

        /**
         * The interfaces of the class.
         */
        List<String> interfaces;

        /**
         * Initialize the class.
         * @param name class name
         * @param superclass class superclass
         * @param modifiers class access modifiers
         * @param interfaces class interfaces
         * @param vm void virtual machine
         */
        Class(String name, String superclass, int modifiers, List<String> interfaces, VirtualMachine* vm);

        /**
         * Initialize the class.
         * @param name class name
         * @param superclass class superclass
         * @param modifiers class access modifiers
         * @param interfaces class interfaces
         * @param vm void virtual machine
         */
        Class(String name, String superclass, List<String> modifiers, List<String> interfaces, VirtualMachine* vm);

        /**
         * Build class methods, fields and inner classes from bytecode class content.
         * @param bytecode class content
         */
        void build(List<String> bytecode);

        /**
         * Debug parsed class and its content.
         */
        void debug();

        // TODO initialize

        /**
         * Retrieve a class method with the given signature.
         * @param name method name
         * @param parameters method parameters
         * @return found method or nullptr
         */
        Method* getMethod(String name, List<String> parameters);

        /**
         * Define a new method in the class.
         * @param method target method
         */
        void defineMethod(Method* method);

        /**
         * Retrieve a class field with the given name.
         * @param name field name
         * @return found field or nullptr
         */
        Field* getField(String name);

        /**
         * Define a new field in the class.
         * @param field target field
         */
        void defineField(Field* field);
    };

    /**
     * Represents a registery of parseable element types.
     */
    enum ElementType {
        CLASS,
        METHOD,
        FIELD,
        NONE
    };
}
