#pragma once

#include "Executable.hpp"

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
         * Debug the parsed method and its content.
         */
        void debug();
    };
}
#endif