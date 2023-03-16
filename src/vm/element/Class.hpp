#pragma once

#include "../VirtualMachine.hpp"

namespace Void {
    class VirtualMachine;

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
    };
}
