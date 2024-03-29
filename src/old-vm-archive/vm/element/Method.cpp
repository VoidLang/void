#include "Method.hpp"
#include "../runtime/Modifier.hpp"
#include "../../util/Strings.hpp"
#include "../../util/Lists.hpp"
#include "../parser/instructions/Invokes.hpp"

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
     * Perform a method call. Copy method arguments form the caller stack to the current stack.
     * Perform operations on the new stack. Put the return value back to the caller stack. If
     * the instance is not null, it is a non-static method call, otherwise it is static.
     * @param vm running virtual machine
     * @param callerStack stack of the method's call context
     * @param instance target instance to perform the method call with, nullptr it is static call
     * @param caller parent caller executable that called this executable
     */
    void Method::invoke(VirtualMachine* vm, Stack* callerStack, Reference<Instance*>* instance, Executable* caller) {
        // create a new stack for the method execution context that will hold values in memory allowing us to perform operations on
        String stackName = clazz->name + "." + name + "(" + Strings::join(parameters, ", ") + ")" + returnType;
        Stack* stack = new Stack(callerStack, this, stackName);

        // create a local variable storage that will hold stack operations' results
        Storage* storage = new Storage();

        // copy the method arguments from the method caller's stack to the current variable storage
        copyArguments(callerStack, storage, instance);

        // TODO declare method call result

        // TODO handle native method call

        // TODO handle a normal method call

        // create the method execution content
        Context* context = new Context(stack, storage, bytecode.size(), this);

        // create a new loop that will execute until a return is called or there is nothing left to be executed
        for (; context->cursor < context->length; context->cursor++) {
            // get the instruction at the current cursor
            Instruction* instruction = bytecode[context->cursor];

            //auto begin = nanoTime();

            // execute the bytecode instruction that will perform stack and storage manipulation
            // this will might modify the cursor, and return a value
            instruction->execute(context);
        
            //auto end = nanoTime();

            //auto name = ELEMENT_INSTRUCTIONS_MAPPED[static_cast<int>(instruction->kind)];

            //println(name << " took " << (end - begin) << "ns" << " " << ((end - begin) / 1000000.0) << "ms");
        }

        // handle the return value of the method call
        handleReturn(context, callerStack);
    }

    /**
     * Copy method call arguments from the caller stack to the variable storage of this execution context.
     * @param callerStack method execution caller stack
     * @param storage method execution context variable storage
     */
    void Method::copyArguments(Stack* callerStack, Storage* storage, Reference<Instance*>* instance) {
        // create storage offsets which are used to indicate which storage unit should a parameter value be copied into
        // when copying a certain type of parameter, the offset is incremented by one
        uint byteOffset     = 0;
        uint charOffset     = 0;
        uint shortOffset    = 0;
        uint intOffset      = 0;
        uint longOffset     = 0;
        uint floatoffset    = 0;
        uint doubleOffset   = 0;
        uint booleanOffset  = 0;
        uint instanceOffset = 0;

        // prepare for a non-static method call, place the "this" instance into the first instance storage slot
        if (instance != nullptr)
            storage->instances.set(instanceOffset++, instance);

        // copy method arguments from the caller stack to the current storage
        for (String parameter : parameters) {
            // get the first character of the parameter type that we are going to test
            // identify what should we do with the parameter
            // array types begins with a "[" prefix, classes with an "L" prefix, and primitives have their own symbols:
            // B (byte), C (char), S (short), I (int), J (long), F (float), D (double), Z (boolean)
            char prefix = parameter[0];

            // handle byte parameter
            if (prefix == 'B')
                storage->bytes.set(byteOffset++, callerStack->bytes.pull());

            // handle char parameter
            else if (prefix == 'C')
                storage->chars.set(charOffset++, callerStack->chars.pull());

            // handle short parameter
            else if (prefix == 'S')
                storage->shorts.set(shortOffset++, callerStack->shorts.pull());

            // handle integer parameter
            else if (prefix == 'I')
                storage->ints.set(intOffset++, callerStack->ints.pull());

            // handle long parameter
            else if (prefix == 'J')
                storage->longs.set(longOffset++, callerStack->longs.pull());

            // handle float parameter
            else if (prefix == 'F')
                storage->floats.set(floatoffset++, callerStack->floats.pull());

            // handle double parameter
            else if (prefix == 'D')
                storage->doubles.set(doubleOffset++, callerStack->doubles.pull());

            // handle boolean parameter
            else if (prefix == 'Z')
                storage->booleans.set(booleanOffset++, callerStack->booleans.pull());

            // handle instance parameter
            // TODO maybe check instance type
            else if (prefix == 'L')
                storage->instances.set(instanceOffset++, callerStack->instances.pull());

            // TODO handle array parameter
        }
    }

    /**
     * Handle the return value of the method execution.
     * @param context method execution context
     * @param callerStack stack of the method's call context
     */
    void Method::handleReturn(Context* context, Stack* callerStack) {
        // ignore the execution result if the return tpye is void
        char prefix = returnType[0];
        // void does not return anything, we don't care about the result
        if (prefix == 'V') 
            return;

        // handle byte return type
        if (prefix == 'B')
            callerStack->bytes.push(object_cast<byte>(context->result));

        // handle char return type
        else if (prefix == 'C')
            callerStack->chars.push(object_cast<cint>(context->result));

        // handle short return type
        else if (prefix == 'S')
            callerStack->shorts.push(object_cast<short>(context->result));

        // handle integer return type
        else if (prefix == 'I')
            callerStack->ints.push(object_cast<int>(context->result));

        // handle long return type
        else if (prefix == 'J')
            callerStack->longs.push(object_cast<lint>(context->result));

        // handle float return type
        else if (prefix == 'F')
            callerStack->floats.push(object_cast<float>(context->result));

        // handle double return type
        else if (prefix == 'D')
            callerStack->doubles.push(object_cast<double>(context->result));

        // handle boolean return type
        else if (prefix == 'Z')
            callerStack->booleans.push(object_cast<bool>(context->result));

        // handle instance return type
        // TODO maybe check instance type
        else if (prefix == 'L')
            callerStack->instances.push(object_cast<Reference<Instance*>*>(context->result));

        // TODO handle array return type
    }

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

    // I know right, this is a tricky solution, however I couldn't come up with anything better.
    // The problem is that InvokeStatic requires Instruction, Method and Class to be parsed.
    // Therefore putting it in "Invokes.cpp" made Method undefined.

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
     * @param executable bytecode executor
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
                    << "(" << Strings::join(methodParameters, " ") << ") of class " << className);
        }
        // statically invoke the class method
        methodRef->invoke(context->executable->vm, context->stack, nullptr, context->executable);
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
