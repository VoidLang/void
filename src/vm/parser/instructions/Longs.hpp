#pragma once

#include "../Instruction.hpp"

#ifdef VOID_INSTRUCTION
namespace Void {
#pragma region LONG_PUSH
    /**
     * Represents an instruction that pushes an long to the stack.
     */
    class LongPush : public Instruction {
    private:
        /**
         * The value to push to the stack.
         */
        lint value = 0;

    public:
        /**
         * Initialize the long push instruction.
         */
        LongPush();

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

#pragma region LONG_LOAD
    /**
     * Represents an instruction that loads an long from the storage.
     */
    class LongLoad : public Instruction {
    private:
        /**
         * The storage index to load the long from.
         */
        uint index = 0;

    public:
        /**
         * Initialize the long load instruction.
         */
        LongLoad();

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

#pragma region LONG_STORE
    /**
     * Represents an instruction that stores an long in the storage.
     */
    class LongStore : public Instruction {
    private:
        /**
         * The storage index to store the long linto.
         */
        uint index = 0;

        /**
         * Determine if the value should be kept on the stack.
         */
        bool keepStack = false;

    public:
        /**
         * Initialize the long store instruction.
         */
        LongStore();

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

#pragma region LONG_SET
    /**
     * Set the value of the given local variable.
     */
    class LongSet : public Instruction {
    private:
        /**
         * The local variable storage index to be assigned.
         */
        uint index = 0;

        /**
         * The value to push to be assigned for the variable.
         */
        lint value = 0;

    public:
        /**
         * Initialize the long set instruction.
         */
        LongSet();

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

#pragma region LONG_ENSURE
    /**
     * Ensure the capacity of the long variable storage.
     */
    class LongEnsure : public Instruction {
    private:
        /**
         * The ensured size of the variable storage.
         */
        uint size = 0;

    public:
        /**
         * Initialize the long ensure instruction.
         */
        LongEnsure();

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

#pragma region LONG_ADD
    /**
     * Represents an instruction that adds two long values.
     */
    class LongAdd : public Instruction {
    private:
        /**
         * The target of te first number in the addition.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        lint firstValue = 0;

        /**
         * Determine if the second number should be loaded from the stack.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        lint secondValue = 0;

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
         * Initialize the long add instruction.
         */
        LongAdd();

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

#pragma region LONG_SUBTRACT
    /**
     * Represents an instruction that subtracts two long values.
     */
    class LongSubtract : public Instruction {
    private:
        /**
         * The target of te first number in the subtraction.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        lint firstValue = 0;

        /**
         * Determine if the second number should be loaded from the stack.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        lint secondValue = 0;

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
         * Initialize the long subtract instruction.
         */
        LongSubtract();

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

#pragma region LONG_MULTIPLY
    /**
     * Represents an instruction that multiplies two long values.
     */
    class LongMultiply : public Instruction {
    private:
        /**
         * The target of te first number in the multiplication.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        lint firstValue = 0;

        /**
         * Determine if the second number should be loaded from the stack.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        lint secondValue = 0;

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
         * Initialize the long multiply instruction.
         */
        LongMultiply();

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

#pragma region LONG_DIVIDE
    /**
     * Represents an instruction that divides two long values.
     */
    class LongDivide : public Instruction {
    private:
        /**
         * The target of te first number in the division.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        lint firstValue = 0;

        /**
         * Determine if the second number should be loaded from the stack.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        lint secondValue = 0;

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
         * Initialize the long divide instruction.
         */
        LongDivide();

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

#pragma region LONG_MODULO
    /**
     * Represents an instruction that divides two long values and results the remainder.
     */
    class LongModulo : public Instruction {
    private:
        /**
         * The target of the first number in the remainder division.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        lint firstValue = 0;

        /**
         * Determine if the second number should be loaded from the stack.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        lint secondValue = 0;

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
         * Initialize the long modulo instruction.
         */
        LongModulo();

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

#pragma region LONG_INCREMENT
    /**
     * Represents an instruction that increments an long by one.
     */
    class LongIncrement : public Instruction {
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
         * Initialize the long increment instruction.
         */
        LongIncrement();

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

#pragma region LONG_DECREMENT
    /**
     * Represents an instruction that decrements an long by one.
     */
    class LongDecrement : public Instruction {
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
         * Initialize the long decrement instruction.
         */
        LongDecrement();

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

#pragma region LONG_NEGATE
    /**
     * Represents an instruction that negates an long.
     */
    class LongNegate : public Instruction {
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
         * Initialize the long negate instruction.
         */
        LongNegate();

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

#pragma region LONG_DEBUG
    /**
     * Represents an instruction that prlints an long value from the stack.
     */
    class LongDebug : public Instruction {
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
         * Initailize the long debug instruction.
         */
        LongDebug();

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

#pragma region LONG_IF_EQUALS
    /**
     * Represents an instruction that jumps to a given section if two longs are equal.
     */
    class LongEquals : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        lint firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        lint secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the long equals check instruction.
         */
        LongEquals();

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

#pragma region LONG_IF_NOT_EQUALS
    /**
     * Represents an instruction that jumps to a given section if two longs are not equal.
     */
    class LongNotEquals : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        lint firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        lint secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the long not equals instruction.
         */
        LongNotEquals();

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

#pragma region LONG_IF_GREATER_THAN
    /**
     * Represents an instruction that jumps to a given section if an long is greater than another.
     */
    class LongGreaterThan : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        lint firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        lint secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the long greater than check instruction.
         */
        LongGreaterThan();

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

#pragma region LONG_IF_GREATER_THAN_OR_EQUAL
    /**
     * Represents an instruction that jumps to a given section if an long is greater than or is equal another.
     */
    class LongGreaterThanOrEquals : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        lint firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        lint secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the long greater than or equal check instruction.
         */
        LongGreaterThanOrEquals();

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

#pragma region LONG_IF_LESS_THAN
    /**
     * Represents an instruction that jumps to a given section if an long is less than another.
     */
    class LongLessThan : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        lint firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        lint secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the long less than check instruction.
         */
        LongLessThan();

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

#pragma region LONG_IF_LESS_THAN_OR_EQUAL
    /**
     * Represents an instruction that jumps to a given section if an long is less than or is equal another.
     */
    class LongLessThanOrEqual : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        lint firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        lint secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the long less than or equal check instruction.
         */
        LongLessThanOrEqual();

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

#pragma region LONG_STACK_SIZE
    /**
     * Represents an instruction that retrieves the size of the long stack and pushes the count to the long stack.
     */
    class LongStackSize : public Instruction {
    public:
        /**
         * Initailize the long stack size instruction.
         */
        LongStackSize();

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

#pragma region LONG_DUMP_STACK
    /**
     * Represents an instruction that dumps the elements of the long stack.
     */
    class LongDumpStack : public Instruction {
    public:
        /**
         * Initialize the long stack dump instruction.
         */
        LongDumpStack();

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

#pragma region LONG_CLEAR_STACK
    /**
     * Represents an instruction that clears the long stack.
     */
    class LongClearStack : public Instruction {
    public:
        /**
         * Initialize the long stack clear instruction.
         */
        LongClearStack();

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

#pragma region LONG_POP_STACK
    /**
     * Represents an instruction that removes an long from the stack.
     */
    class LongPopStack : public Instruction {
    public:
        /**
         * Initialize the long pop instruction.
         */
        LongPopStack();

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

#pragma region LONG_DUPLICATE_STACK
    /**
     * Represents an instruction that duplicates an long on the stack.
     */
    class LongDuplicateStack : public Instruction {
    private:
        /**
         * The number of times the long should be duplicated.
         */
        uint count = 1;

    public:
        /**
         * Initialize the long duplicate instruction.
         */
        LongDuplicateStack();

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