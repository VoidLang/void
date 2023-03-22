#pragma once

#include "../Instruction.hpp"

#ifdef VOID_INSTRUCTION
namespace Void {
#pragma region INTEGER_PUSH
    /**
     * Represents an instruction that pushes an integer to the stack.
     */
    class IntegerPush : public Instruction {
    private:
        /**
         * The value to push to the stack.
         */
        int value;

    public:
        /**
         * Initialize the integer push instruction.
         */
        IntegerPush();

        /**
         * Parse raw bytecode instruction.
         * @param raw bytecode data
         * @parma args split array of the data
         * @param line bytecode line index
         * @aram executable bytecode executor
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

#pragma region INTEGER_LOAD
    /**
     * Represents an instruction that loads an integer from the storage.
     */
    class IntegerLoad : public Instruction {
    private:
        /**
         * The storage index to load the integer from.
         */
        uint index;

    public:
        /**
         * Initialize the integer load instruction.
         */
        IntegerLoad();

        /**
         * Parse raw bytecode instruction.
         * @param raw bytecode data
         * @parma args split array of the data
         * @param line bytecode line index
         * @aram executable bytecode executor
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

#pragma region INTEGER_STORE
    /**
     * Represents an instruction that stores an integer in the storage.
     */
    class IntegerStore : public Instruction {
    private:
        /**
         * The storage index to store the integer into.
         */
        uint index;

        /**
         * Determine if the value should be kept on the stack.
         */
        bool keepStack = false;

    public:
        /**
         * Initialize the integer store instruction.
         */
        IntegerStore();

        /**
         * Parse raw bytecode instruction.
         * @param raw bytecode data
         * @parma args split array of the data
         * @param line bytecode line index
         * @aram executable bytecode executor
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

#pragma region INTEGER_SET
    /**
     * Set the value of the given local variable.
     */
    class IntegerSet : public Instruction {
    private:
        /**
         * The local variable storage index to be assigned.
         */
        uint index;

        /**
         * The value to push to be assigned for the variable.
         */
        int value;

    public:
        /**
         * Initialize the integer set instruction.
         */
        IntegerSet();

        /**
         * Parse raw bytecode instruction.
         * @param raw bytecode data
         * @parma args split array of the data
         * @param line bytecode line index
         * @aram executable bytecode executor
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

#pragma region INTEGER_ENSURE
    /**
     * Ensure the capacity of the integer variable storage.
     */
    class IntegerEnsure : public Instruction {
    private:
        /**
         * The ensured size of the variable storage.
         */
        uint size;

    public:
        /**
         * Initialize the integer ensure instruction.
         */
        IntegerEnsure();

        /**
         * Parse raw bytecode instruction.
         * @param raw bytecode data
         * @parma args split array of the data
         * @param line bytecode line index
         * @aram executable bytecode executor
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

#pragma region INTEGER_DEBUG
    /**
     * Represents an instruction that prints an integer value from the stack.
     */
    class IntegerDebug : public Instruction {
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
         * Initailize the integer debug instruction.
         */
        IntegerDebug();

        /**
         * Parse raw bytecode instruction.
         * @param raw bytecode data
         * @parma args split array of the data
         * @param line bytecode line index
         * @aram executable bytecode executor
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