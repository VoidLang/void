#pragma once

#include "../Instruction.hpp"

#ifdef VOID_INSTRUCTION
namespace Void {
#pragma region NEW
    /**
     * Represents an instruction that creates a new instance of the given class type.
     */
    class New : public Instruction {
    private:
        /**
         * The name of the target class.
         */
        String className;

        /**
         * The reference of the target class.
         */
        Class* classRef = nullptr;

        /**
         * The target of the instance creation result.
         */
        Target resultTarget = Target::STACK;

        /**
         * The index of the result variable.
         */
        uint resultLocalIndex = 0;

    public:
        /**
         * Initialize the instance creation instruction.
         */
        New();

        /**
         * Parse raw bytecode instruction.
         * @param raw bytecode data
         * @parma args split array of the data
         * @param line bytecode line index
         * @param executable bytecode executor
         */
        void parse(String data, List<String> args, uint line, Executable* executable) override;

        /**
         * Initialize the references in the const pool after the whole program has been parsed.
         * @param vm running virtual machine
         * @param executable bytecode executor
         */
        void initialize(VirtualMachine* vm, Executable* executable) override;

        /**
         * Execute the instruction in the executable context.
         * @param context bytecode execution context
         */
        void execute(Context* context) override;

        /**
         * Get the string representation of the instruction.
         * @return instruction bytecode data
         */
        String debug() override;
    };
#pragma endregion

#pragma region NULLPTR
    /**
     * Represents an instruction that pushes a null pointer reference to the stack.
     */
    class Nullptr : public Instruction {
    public:
        /**
         * Initialize the null pointer push instruction.
         */
        Nullptr();

        /**
         * Execute the instruction in the executable context.
         * @param context bytecode execution context
         */
        void execute(Context* context) override;

        /**
         * Get the string representation of the instruction.
         * @return instruction bytecode data
         */
        String debug() override;
    };
#pragma endregion

#pragma region INSTANCE_DELETE
    /**
     * Represents an instruction that deletes an instance from the memory.
     */
    class InstanceDelete : public Instruction {
    private:
        /**
         * The target of the instance deletion source.
         */
        Target source = Target::STACK;

        /**
         * The storage index of the instance deletion source.
         */
        uint sourceIndex = 0;

    public:
        /**
         * Initialize the instance deletion instruction.
         */
        InstanceDelete();

        /**
         * Parse raw bytecode instruction.
         * @param raw bytecode data
         * @parma args split array of the data
         * @param line bytecode line index
         * @param executable bytecode executor
         */
        void parse(String data, List<String> args, uint line, Executable* executable) override;

        /**
         * Execute the instruction in the executable context.
         * @param context bytecode execution context
         */
        void execute(Context* context) override;

        /**
         * Get the string representation of the instruction.
         * @return instruction bytecode data
         */
        String debug() override;
    };
#pragma endregion

#pragma region INSTANCE_GET_ADDRESS
    /**
     * Represents an instruction that retrieves the memory address of an instance.
     */
    class InstanceGetAddress : public Instruction {
    private:
        /**
         * The target of the instance reference source.
         */
        Target source = Target::STACK;

        /**
         * The storage index of the instance reference source.
         */
        uint sourceIndex = 0;

        /**
         * The target of the instance address result.
         */
        Target result = Target::STACK;

        /**
         * The storage index of the instance address result.
         */
        uint resultIndex = 0;

    public:
        /**
         * Initialize the instance address get instruction.
         */
        InstanceGetAddress();

        /**
         * Parse raw bytecode instruction.
         * @param raw bytecode data
         * @parma args split array of the data
         * @param line bytecode line index
         * @param executable bytecode executor
         */
        void parse(String data, List<String> args, uint line, Executable* executable) override;

        /**
         * Execute the instruction in the executable context.
         * @param context bytecode execution context
         */
        void execute(Context* context) override;

        /**
         * Get the string representation of the instruction.
         * @return instruction bytecode data
         */
        String debug() override;
    };
#pragma endregion

#pragma region INSTANCE_SET_ADDRESS
    /**
     * Rpresents an instruction that sets the instruction pointer value at the given long address.
     */
    class InstanceSetAddress : public Instruction {
    private:
        /**
         * The target of the instance address source.
         */
        Target source = Target::STACK;

        /**
         * The storage index of the instance address source.
         */
        uint sourceIndex = 0;

        /**
         * The target of the instance reference result.
         */
        Target result = Target::STACK;

        /**
         * The storage index of the instance reference result.
         */
        uint resultIndex = 0;

    public:
        /**
         * Initialize the instance reference set instruction..
         */
        InstanceSetAddress();

        /**
         * Parse raw bytecode instruction.
         * @param raw bytecode data
         * @parma args split array of the data
         * @param line bytecode line index
         * @param executable bytecode executor
         */
        void parse(String data, List<String> args, uint line, Executable* executable) override;

        /**
         * Execute the instruction in the executable context.
         * @param context bytecode execution context
         */
        void execute(Context* context) override;

        /**
         * Get the string representation of the instruction.
         * @return instruction bytecode data
         */
        String debug() override;
    };
#pragma endregion

#pragma region INSTANCE_LOAD
    /**
     * Represents an instruction that loads an instance from the storage and puts the value on the stack.
     */
    class InstanceLoad : public Instruction {
    private:
        /**
         * The storage index to load the instance from.
         */
        uint index = 0;

    public:
        /**
         * Initialize the instance load instruction.
         */
        InstanceLoad();

        /**
         * Parse raw bytecode instruction.
         * @param raw bytecode data
         * @parma args split array of the data
         * @param line bytecode line index
         * @param executable bytecode executor
         */
        void parse(String data, List<String> args, uint line, Executable* executable) override;

        /**
         * Execute the instruction in the executable context.
         * @param context bytecode execution context
         */
        void execute(Context* context) override;

        /**
         * Get the string representation of the instruction.
         * @return instruction bytecode data
         */
        String debug() override;
    };
#pragma endregion

#pragma region INSTANCE_STORE
    /**
     * Represents an instruction that stores an instance value in the storage from the stack.
     */
    class InstanceStore : public Instruction {
    private:
        /**
         * The storage index to store the instance into.
         */
        uint index = 0;

        /**
        * Determine if the value should be kept on the stack.
        */
        bool keepStack = false;

    public:
        /**
         * Initialize the instance 
         */
        InstanceStore();

        /**
         * Parse raw bytecode instruction.
         * @param raw bytecode data
         * @parma args split array of the data
         * @param line bytecode line index
         * @param executable bytecode executor
         */
        void parse(String data, List<String> args, uint line, Executable* executable) override;

        /**
         * Execute the instruction in the executable context.
         * @param context bytecode execution context
         */
        void execute(Context* context) override;

        /**
         * Get the string representation of the instruction.
         * @return instruction bytecode data
         */
        String debug() override;
    };
#pragma endregion

#pragma region INSTANCE_DEBUG
    /**
     * Represents an instruction that debugs an instance value from the stack.
     */
    class InstanceDebug : public Instruction {
    private:
        /**
         * Determine if a new line should be inserted after the debug.
         */
        bool newLine = false;

        /**
         * Determine if the value should be kept on the stack.
         */
        bool keepStack = false;

    public:
        /**
         * Initialize the instance debug instruction.
         */
        InstanceDebug();

        /**
         * Parse raw bytecode instruction.
         * @param raw bytecode data
         * @parma args split array of the data
         * @param line bytecode line index
         * @param executable bytecode executor
         */
        void parse(String data, List<String> args, uint line, Executable* executable) override;

        /**
         * Execute the instruction in the executable context.
         * @param context bytecode execution context
         */
        void execute(Context* context) override;

        /**
         * Get the string representation of the instruction.
         * @return instruction bytecode data
         */
        String debug() override;
    };
#pragma endregion
}
#endif