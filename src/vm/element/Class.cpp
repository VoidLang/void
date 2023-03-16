#include "Class.hpp"

namespace Void {
    /**
     * Initialize the class.
     * @param name class name
     * @param superclass class superclass
     * @param modifiers class access modifiers
     * @param interfaces class interfaces
     * @param vm void virtual machine
     */
    Class::Class(String name, String superclass, int modifiers, List<String> interfaces, VirtualMachine* vm)
        : name(name), superclass(superclass), modifiers(modifiers), interfaces(interfaces), vm(vm)
    { }

    /**
     * Initialize the class.
     * @param name class name
     * @param superclass class superclass
     * @param modifiers class access modifiers
     * @param interfaces class interfaces
     * @param vm void virtual machine
     */
    Class::Class(String name, String superclass, List<String> modifiers, List<String> interfaces, VirtualMachine* vm)
        : name(name), superclass(superclass), modifiers(0 /* TODO */), interfaces(interfaces), vm(vm)
    { }

    /**
     * Build class methods, fields and inner classes from bytecode class content.
     * @param bytecode class content
     */
    void Class::build(List<String> bytecode) {
    }

    /**
     * Debug parsed class and its content.
     */
    void Class::debug() {
        println("class " << name);
    }
}