#include "Method.hpp"
#include "../runtime/Modifier.hpp"
#include "../../util/Strings.hpp"

namespace Void {
    /**
     * Initialize the class method.
     * @param name method name
     * @param return type
     * @param modifiers method access modifiers
     * @param parameters method parameter list
     * @param clazz method parent class
     * @param vm running virtual machine
     */
    Method::Method(String name, String returnType, List<String> modifiers, List<String> parameters, Class* clazz, VirtualMachine* vm)
        : Executable(modifiers, vm, clazz), name(name), returnType(returnType), parameters(parameters)
    { }

    /**
     * Debug the parsed method and its content.
     */
    void Method::debug() {
        // print some indentation for the method
        print("    ");

        // debug the method modifiers
        List<String>modifiers = parseModifiers(this->modifiers);
        if (!modifiers.empty())
            print(Strings::join(modifiers, " ") << ' ');

        // debug the method return type and name
        print(returnType << ' ' << name);

        // debug the method parameters
        print('(' << Strings::join(parameters, ", ") << ')');

        // do not debug the method body if it is native or abstract
        if (hasModifier(Modifier::NATIVE) || hasModifier(Modifier::ABSTRACT)) {
            // end method body debugging
            println(";");
            return;
        }

        // debug the method body
        println(" {");

        for (uint i = 0; i < bytecode.size(); i++)
            println("        " << i << ": " << bytecode[i]->debug());
        
        println("    }");
    }
}
