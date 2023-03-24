#include "Instances.hpp"

namespace Void {
#pragma region NEW
    /**
     * Initialize the instance creation instruction.
     */
    New::New()
        : Instruction(Instructions::NEW)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void New::parse(String data, List<String> args, uint line, Executable* executable) {
        // parse the target class name
        className = args[0];
    }

    /**
     * Initialize the references in the const pool after the whole program has been parsed.
     * @param vm running virtual machine
     * @param executable bytecode executor
     */
    void New::initialize(VirtualMachine* vm, Executable* executable) {
        // get the class reference from the virtual machine
        classRef = vm->getClass(className);
        // we don't need to check if the class is actually found here, as 
        // it might be loaded afterwards
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void New::execute(Context* context) {
        // check if the class is missing
        if (classRef == nullptr) {
            // try to load the class reference again, as it was possibly lodaded
            // after this instruction was initialized
            classRef = context->executable->vm->getClass(className);
            // check if the class is still missing
            if (classRef == nullptr)
                // TODO throw an error instead of panicing
                error("NoSuchClassException: Trying to create instance of undefined class " << className);
        }

        // create a new instance of the class
        Instance* instance = new Instance(classRef);
        // create a wrapper smart pointer for the instance
        Reference<Instance*>* reference = new Reference(instance);

        // copy the non-static class fields to the instance
        instance->copyFields(context->executable->vm, context->stack, reference);

        // TODO push the created class onto the instance class
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String New::debug() {
        return "new " + className;
    }
#pragma endregion

#pragma region NULLPTR
    /**
     * Initialize the null pointer push instruction.
     */
    Nullptr::Nullptr()
        : Instruction(Instructions::NULLPTR)
    { }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void Nullptr::execute(Context* context) {
        context->stack->instances.push(nullptr);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String Nullptr::debug() {
        return "nullptr";
    }
#pragma endregion

#pragma region INSTANCE_DELETE
    /**
     * Initialize the instance deletion instruction.
     */
    InstanceDelete::InstanceDelete()
        : Instruction(Instructions::INSTANCE_DELETE)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void InstanceDelete::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                source = Target::LOCAL;
                sourceIndex = executable->getLinker(args[++i]);
            }
        }
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void InstanceDelete::execute(Context* context) {
        // get the instance to be deleted
        Reference<Instance*>* reference = nullptr;
        switch (source) {
            case Target::STACK:
                reference = context->stack->instances.pull();
                break;
            case Target::LOCAL:
                reference = context->storage->instances.get(sourceIndex);
                break;
        }
        // delete the reference data from memory
        if (reference != nullptr)
            reference->purge();
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String InstanceDelete::debug() {
        String result = "delete";
        switch (source) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local";
                break;
        }
        return result;
    }
#pragma endregion

#pragma region INSTANCE_GET_ADDRESS
    /**
     * Initialize the instance address get instruction.
     */
    InstanceGetAddress::InstanceGetAddress()
        : Instruction(Instructions::INSTANCE_GET_ADDRESS)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void InstanceGetAddress::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                source = Target::LOCAL;
                sourceIndex = executable->getLinker(args[++i]);
            }
            // handle addition result
            else if (arg == "-r" || arg == "-result") {
                result = Target::LOCAL;
                resultIndex = executable->getLinker(args[++i]);
            }
        }
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void InstanceGetAddress::execute(Context* context) {
        // get the instance to be handled
        Reference<Instance*>* reference = nullptr;
        switch (source) {
            case Target::STACK:
                reference = context->stack->instances.pull();
                break;
            case Target::LOCAL:
                reference = context->storage->instances.get(sourceIndex);
                break;
        }
        // check if the reference is null
        if (reference == nullptr || !reference->exists) 
            context->stack->longs.push(0);
        else {
            // get the address of the instance as long
            lint address = reinterpret_cast<lint>(reference);
            context->stack->longs.push(address);
        }
            
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String InstanceGetAddress::debug() {
        return "getaddr";
    }
#pragma endregion
}