#pragma once

#include "Executable.hpp"
#include "../runtime/Reference.hpp"

#ifdef VOID_EXECUTABLE
namespace Void {
    /**
     * Represents a class method in the virtual machine.
     * A method can compute seperate calculation. 
     * It has an input parameter list, and an output return type.
     */
    class Method : public Executable {
    public:
        /**
         * The name of the method.
         */
        String name;

        /**
         * The return type of the method.
         */
        String returnType;
    
        /**
         * The parameter list of the method.
         */
        List<String> parameters;

        // TODO Native method execution handle.
   
        /**
         * Initialize the class method. 
         * @param name method name
         * @param return type
         * @param modifiers method access modifiers
         * @param parameters method parameter list
         * @param clazz method parent class
         * @param vm running virtual machine
         */

        Method(String name, String returnType, List<String> modifiers, List<String> parameters, Class* clazz, VirtualMachine* vm);


        /**
         * Perform a method call. Copy method arguments form the caller stack to the current stack. 
         * Perform operations on the new stack. Put the return value back to the caller stack. If 
         * the instance is not null, it is a non-static method call, otherwise it is static.
         */
        // void invoke(VirtualMachine* vm, Stack* callerStack, Reference<Instance>)

        /**
         * Debug the parsed method and its content.
         */
        void debug();
    };
}
#endif