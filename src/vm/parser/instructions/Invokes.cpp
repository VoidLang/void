#include "Invokes.hpp"

#include "../../../util/Lists.hpp"
#include "../../../util/Strings.hpp"

namespace Void {
#pragma region INVOKE_STATIC
    /**
     * Initialize static method invoke instruction.
     */
    InvokeStatic::InvokeStatic()
        : Instruction(Instructions::INVOKE_STATIC)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void InvokeStatic::parse(String data, List<String> args, uint line, Executable* executable) {
        // parse the target class name
        className = args[0];
        // parse the target method name
        methodName = args[1];
        // parse the method parameters
        methodParameters = Lists::subList(args, 2);
    }

    /**
     * Initialize the references in the const pool after the whole program has been parsed.
     * @param vm running virtual machine
     * @param executable bytecode executor
     */
    void InvokeStatic::initialize(VirtualMachine* vm, Executable* executable) {
        // get the class reference from the virtual machine
        classRef = vm->getClass(className);
        // we don't need to check if the class is actually found here, as 
        // it might be loaded afterwards

        // get the method reference if the class reference was found
        if (classRef != nullptr) {
            // get the method reference from the class
            methodRef = classRef->getMethod(methodName, methodParameters);
            // here again we don't care if the method reference is not found
            // as there are chances this code will not be executed
        }
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void InvokeStatic::execute(Context* context) {
        // check if the class reference is missing
        if (classRef == nullptr) {
            // try to load the class reference again, as it was possibly lodaded
            // after this instruction was initialized
            classRef = context->executable->vm->getClass(className);
            // check if the class is still missing
            if (classRef == nullptr)
                // TODO throw an error instead of panicing
                error("NoSuchClassException: Trying to invoke static method of undefined class " << className);
        }
        // check if the method reference is missing
        if (methodRef == nullptr) {
            // get the method reference from the class
            methodRef = classRef->getMethod(methodName, methodParameters);
            // check if the method reference is still missing
            if (methodRef == nullptr)
                // TODO throw an error instead of panicing
                error("NoSuchMethodException: Trying to invoke undefined static method " << methodName
                    << "(" << Strings::join(methodParameters, " ") << " of class " << className);
        }
        // statically invoke the class method
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String InvokeStatic::debug() {
        return "invokestatic " + className + " " + methodName + " " + Strings::join(methodParameters, " ");
    }
#pragma endregion
}