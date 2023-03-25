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
        int value = 0;

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

#pragma region INTEGER_LOAD
    /**
     * Represents an instruction that loads an integer from the storage.
     */
    class IntegerLoad : public Instruction {
    private:
        /**
         * The storage index to load the integer from.
         */
        uint index = 0;

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

#pragma region INTEGER_STORE
    /**
     * Represents an instruction that stores an integer in the storage.
     */
    class IntegerStore : public Instruction {
    private:
        /**
         * The storage index to store the integer into.
         */
        uint index = 0;

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

#pragma region INTEGER_SET
    /**
     * Set the value of the given local variable.
     */
    class IntegerSet : public Instruction {
    private:
        /**
         * The local variable storage index to be assigned.
         */
        uint index = 0;

        /**
         * The value to push to be assigned for the variable.
         */
        int value = 0;

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

#pragma region INTEGER_ENSURE
    /**
     * Ensure the capacity of the integer variable storage.
     */
    class IntegerEnsure : public Instruction {
    private:
        /**
         * The ensured size of the variable storage.
         */
        uint size = 0;

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

#pragma region INTEGER_ADD
    /**
     * Represents an instruction that adds two integer values.
     */
    class IntegerAdd : public Instruction {
    private:
        /**
         * The target of te first number in the addition.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        int firstValue = 0;

        /**
         * Determine if the second number should be loaded from the stack.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        int secondValue = 0;

        /**
         * The target of the addition result.
         */
        Target resultTarget = Target::STACK;

        /**
         * The index of the result variable.
         */
        uint resultLocalIndex = 0;

    public:
        /**
         * Initialize the integer add instruction. 
         */
        IntegerAdd();

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

#pragma region INTEGER_SUBTRACT
    /**
     * Represents an instruction that subtracts two integer values.
     */
    class IntegerSubtract : public Instruction {
    private:
        /**
         * The target of te first number in the subtraction.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        int firstValue = 0;

        /**
         * Determine if the second number should be loaded from the stack.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        int secondValue = 0;

        /**
         * The target of the subtraction result.
         */
        Target resultTarget = Target::STACK;

        /**
         * The index of the result variable.
         */
        uint resultLocalIndex = 0;

    public:
        /**
         * Initialize the integer subtract instruction.
         */
        IntegerSubtract();

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

#pragma region INTEGER_MULTIPLY
    /**
     * Represents an instruction that multiplies two integer values.
     */
    class IntegerMultiply : public Instruction {
    private:
        /**
         * The target of te first number in the multiplication.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        int firstValue = 0;

        /**
         * Determine if the second number should be loaded from the stack.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        int secondValue = 0;

        /**
         * The target of the multiplication result.
         */
        Target resultTarget = Target::STACK;

        /**
         * The index of the result variable.
         */
        uint resultLocalIndex = 0;

    public:
        /**
         * Initialize the integer multiply instruction.
         */
        IntegerMultiply();

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

#pragma region INTEGER_DIVIDE
    /**
     * Represents an instruction that divides two integer values.
     */
    class IntegerDivide : public Instruction {
    private:
        /**
         * The target of te first number in the division.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        int firstValue = 0;

        /**
         * Determine if the second number should be loaded from the stack.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        int secondValue = 0;

        /**
         * The target of the division result.
         */
        Target resultTarget = Target::STACK;

        /**
         * The index of the result variable.
         */
        uint resultLocalIndex = 0;

    public:
        /**
         * Initialize the integer divide instruction.
         */
        IntegerDivide();

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

#pragma region INTEGER_MODULO
    /**
     * Represents an instruction that divides two integer values and results the remainder.
     */
    class IntegerModulo : public Instruction {
    private:
        /**
         * The target of the first number in the remainder division.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        int firstValue = 0;

        /**
         * Determine if the second number should be loaded from the stack.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        int secondValue = 0;

        /**
         * The target of the remainder division result.
         */
        Target resultTarget = Target::STACK;

        /**
         * The index of the result variable.
         */
        uint resultLocalIndex = 0;

    public:
        /**
         * Initialize the integer modulo instruction.
         */
        IntegerModulo();

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

#pragma region INTEGER_INCREMENT
    /**
     * Represents an instruction that increments an integer by one.
     */
    class IntegerIncrement : public Instruction {
    private:
        /**
         * The target of the incremention source.
         */
        Target source = Target::STACK;

        /**
         * The storage index of the incremention source.
         */
        uint sourceIndex = 0;

        /**
         * The target of the incremention result. 
         */
        Target result = Target::STACK;

        /**
         * The storage index of the incremention result.
         */
        uint resultIndex = 0;

    public:
        /**
         * Initialize the integer increment instruction.
         */
        IntegerIncrement();

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

#pragma region INTEGER_DECREMENT
    /**
     * Represents an instruction that decrements an integer by one.
     */
    class IntegerDecrement : public Instruction {
    private:
        /**
         * The target of the decremention source.
         */
        Target source = Target::STACK;

        /**
         * The storage index of the decremention source.
         */
        uint sourceIndex = 0;

        /**
         * The target of the decremention result.
         */
        Target result = Target::STACK;

        /**
         * The storage index of the decremention result.
         */
        uint resultIndex = 0;

    public:
        /**
         * Initialize the integer decrement instruction.
         */
        IntegerDecrement();

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

#pragma region INTEGER_NEGATE
    /**
     * Represents an instruction that negates an integer.
     */
    class IntegerNegate : public Instruction {
    private:
        /**
         * The target of the negation source.
         */
        Target source = Target::STACK;

        /**
         * The storage index of the negation source.
         */
        uint sourceIndex = 0;

        /**
         * The target of the negation result.
         */
        Target result = Target::STACK;

        /**
         * The storage index of the negation result.
         */
        uint resultIndex = 0;

    public:
        /**
         * Initialize the integer negate instruction.
         */
        IntegerNegate();

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

#pragma region INTEGER_RETURN
    /**
     * Represents an instruction that terminates the method execution and puts the return value to the caller stack.
     */
    class IntegerReturn : public Instruction {
    private:
        /**
         * The target of the return value source.
         */
        Target source = Target::STACK;

        /**
         * The storage index of the return value source or the storage index.
         */
        int sourceValue = 0;

    public:
        /**
         * Initialize the integer return instruction.
         */
        IntegerReturn();

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

#pragma region INTEGER_IF_EQUALS
    /**
     * Represents an instruction that jumps to a given section if two integers are equal.
     */
    class IntegerEquals : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        int firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        int secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the integer equals check instruction.
         */
        IntegerEquals();

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

#pragma region INTEGER_IF_NOT_EQUALS
    /**
     * Represents an instruction that jumps to a given section if two integers are not equal.
     */
    class IntegerNotEquals : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        int firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        int secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the integer not equals instruction.
         */
        IntegerNotEquals();

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

#pragma region INTEGER_IF_GREATER_THAN
    /**
     * Represents an instruction that jumps to a given section if an integer is greater than another.
     */
    class IntegerGreaterThan : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        int firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        int secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the integer greater than check instruction.
         */
        IntegerGreaterThan();

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

#pragma region INTEGER_IF_GREATER_THAN_OR_EQUAL
    /**
     * Represents an instruction that jumps to a given section if an integer is greater than or is equal another.
     */
    class IntegerGreaterThanOrEquals : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        int firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        int secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the integer greater than or equal check instruction.
         */
        IntegerGreaterThanOrEquals();

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

#pragma region INTEGER_IF_LESS_THAN
    /**
     * Represents an instruction that jumps to a given section if an integer is less than another.
     */
    class IntegerLessThan : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        int firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        int secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the integer less than check instruction.
         */
        IntegerLessThan();

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

#pragma region INTEGER_IF_LESS_THAN_OR_EQUAL
    /**
     * Represents an instruction that jumps to a given section if an integer is less than or is equal another.
     */
    class IntegerLessThanOrEqual : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        int firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        int secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the integer less than or equal check instruction.
         */
        IntegerLessThanOrEqual();

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

#pragma region INTEGER_STACK_SIZE
    /**
     * Represents an instruction that retrieves the size of the integer stack and pushes the count to the integer stack.
     */
    class IntegerStackSize : public Instruction {
    public:
        /**
         * Initailize the integer stack size instruction. 
         */
        IntegerStackSize();

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

#pragma region INTEGER_DUMP_STACK
    /**
     * Represents an instruction that dumps the elements of the integer stack.
     */
    class IntegerDumpStack : public Instruction {
    public:
        /**
         * Initialize the integer stack dump instruction.
         */
        IntegerDumpStack();

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

#pragma region INTEGER_CLEAR_STACK
    /**
     * Represents an instruction that clears the integer stack.
     */
    class IntegerClearStack : public Instruction {
    public:
        /**
         * Initialize the integer stack clear instruction.
         */
        IntegerClearStack();

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

#pragma region INTEGER_POP_STACK
    /**
     * Represents an instruction that removes an integer from the stack.
     */
    class IntegerPopStack : public Instruction {
    public:
        /**
         * Initialize the integer pop instruction.
         */
        IntegerPopStack();

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

#pragma region INTEGER_DUPLICATE_STACK
    /**
     * Represents an instruction that duplicates an integer on the stack.
     */
    class IntegerDuplicateStack : public Instruction {
    private:
        /**
         * The number of times the integer should be duplicated.
         */
        uint count = 1;

    public:
        /**
         * Initialize the integer duplicate instruction.
         */
        IntegerDuplicateStack();

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