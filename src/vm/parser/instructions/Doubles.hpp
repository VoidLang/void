#pragma once

#include "../Instruction.hpp"

#ifdef VOID_INSTRUCTION
namespace Void {
#pragma region DOUBLE_PUSH
    /**
     * Represents an instruction that pushes an double to the stack.
     */
    class DoublePush : public Instruction {
    private:
        /**
         * The value to push to the stack.
         */
        double value = 0;

    public:
        /**
         * Initialize the double push instruction.
         */
        DoublePush();

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

#pragma region DOUBLE_LOAD
    /**
     * Represents an instruction that loads an double from the storage.
     */
    class DoubleLoad : public Instruction {
    private:
        /**
         * The storage index to load the double from.
         */
        uint index = 0;

    public:
        /**
         * Initialize the double load instruction.
         */
        DoubleLoad();

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

#pragma region DOUBLE_STORE
    /**
     * Represents an instruction that stores an double in the storage.
     */
    class DoubleStore : public Instruction {
    private:
        /**
         * The storage index to store the double doubleo.
         */
        uint index = 0;

        /**
         * Determine if the value should be kept on the stack.
         */
        bool keepStack = false;

    public:
        /**
         * Initialize the double store instruction.
         */
        DoubleStore();

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

#pragma region DOUBLE_SET
    /**
     * Set the value of the given local variable.
     */
    class DoubleSet : public Instruction {
    private:
        /**
         * The local variable storage index to be assigned.
         */
        uint index = 0;

        /**
         * The value to push to be assigned for the variable.
         */
        double value = 0;

    public:
        /**
         * Initialize the double set instruction.
         */
        DoubleSet();

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

#pragma region DOUBLE_ENSURE
    /**
     * Ensure the capacity of the double variable storage.
     */
    class DoubleEnsure : public Instruction {
    private:
        /**
         * The ensured size of the variable storage.
         */
        uint size = 0;

    public:
        /**
         * Initialize the double ensure instruction.
         */
        DoubleEnsure();

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

#pragma region DOUBLE_ADD
    /**
     * Represents an instruction that adds two double values.
     */
    class DoubleAdd : public Instruction {
    private:
        /**
         * The target of te first number in the addition.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        double firstValue = 0;

        /**
         * Determine if the second number should be loaded from the stack.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        double secondValue = 0;

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
         * Initialize the double add instruction.
         */
        DoubleAdd();

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

#pragma region DOUBLE_SUBTRACT
    /**
     * Represents an instruction that subtracts two double values.
     */
    class DoubleSubtract : public Instruction {
    private:
        /**
         * The target of te first number in the subtraction.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        double firstValue = 0;

        /**
         * Determine if the second number should be loaded from the stack.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        double secondValue = 0;

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
         * Initialize the double subtract instruction.
         */
        DoubleSubtract();

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

#pragma region DOUBLE_MULTIPLY
    /**
     * Represents an instruction that multiplies two double values.
     */
    class DoubleMultiply : public Instruction {
    private:
        /**
         * The target of te first number in the multiplication.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        double firstValue = 0;

        /**
         * Determine if the second number should be loaded from the stack.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        double secondValue = 0;

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
         * Initialize the double multiply instruction.
         */
        DoubleMultiply();

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

#pragma region DOUBLE_DIVIDE
    /**
     * Represents an instruction that divides two double values.
     */
    class DoubleDivide : public Instruction {
    private:
        /**
         * The target of te first number in the division.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        double firstValue = 0;

        /**
         * Determine if the second number should be loaded from the stack.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        double secondValue = 0;

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
         * Initialize the double divide instruction.
         */
        DoubleDivide();

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

#pragma region DOUBLE_MODULO
    /**
     * Represents an instruction that divides two double values and results the remainder.
     */
    class DoubleModulo : public Instruction {
    private:
        /**
         * The target of the first number in the remainder division.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        double firstValue = 0;

        /**
         * Determine if the second number should be loaded from the stack.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        double secondValue = 0;

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
         * Initialize the double modulo instruction.
         */
        DoubleModulo();

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

#pragma region DOUBLE_INCREMENT
    /**
     * Represents an instruction that increments an double by one.
     */
    class DoubleIncrement : public Instruction {
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
         * Initialize the double increment instruction.
         */
        DoubleIncrement();

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

#pragma region DOUBLE_DECREMENT
    /**
     * Represents an instruction that decrements an double by one.
     */
    class DoubleDecrement : public Instruction {
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
         * Initialize the double decrement instruction.
         */
        DoubleDecrement();

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

#pragma region DOUBLE_NEGATE
    /**
     * Represents an instruction that negates an double.
     */
    class DoubleNegate : public Instruction {
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
         * Initialize the double negate instruction.
         */
        DoubleNegate();

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

#pragma region DOUBLE_DEBUG
    /**
     * Represents an instruction that double:prs an double value from the stack.
     */
    class DoubleDebug : public Instruction {
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
         * Initailize the double debug instruction.
         */
        DoubleDebug();

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

#pragma region DOUBLE_IF_EQUALS
    /**
     * Represents an instruction that jumps to a given section if two doubles are equal.
     */
    class DoubleEquals : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        double firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        double secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the double equals check instruction.
         */
        DoubleEquals();

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

#pragma region DOUBLE_IF_NOT_EQUALS
    /**
     * Represents an instruction that jumps to a given section if two doubles are not equal.
     */
    class DoubleNotEquals : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        double firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        double secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the double not equals instruction.
         */
        DoubleNotEquals();

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

#pragma region DOUBLE_IF_GREATER_THAN
    /**
     * Represents an instruction that jumps to a given section if an double is greater than another.
     */
    class DoubleGreaterThan : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        double firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        double secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the double greater than check instruction.
         */
        DoubleGreaterThan();

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

#pragma region DOUBLE_IF_GREATER_THAN_OR_EQUAL
    /**
     * Represents an instruction that jumps to a given section if an double is greater than or is equal another.
     */
    class DoubleGreaterThanOrEquals : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        double firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        double secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the double greater than or equal check instruction.
         */
        DoubleGreaterThanOrEquals();

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

#pragma region DOUBLE_IF_LESS_THAN
    /**
     * Represents an instruction that jumps to a given section if an double is less than another.
     */
    class DoubleLessThan : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        double firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        double secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the double less than check instruction.
         */
        DoubleLessThan();

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

#pragma region DOUBLE_IF_LESS_THAN_OR_EQUAL
    /**
     * Represents an instruction that jumps to a given section if an double is less than or is equal another.
     */
    class DoubleLessThanOrEqual : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        double firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        double secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the double less than or equal check instruction.
         */
        DoubleLessThanOrEqual();

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

#pragma region DOUBLE_STACK_SIZE
    /**
     * Represents an instruction that retrieves the size of the double stack and pushes the count to the double stack.
     */
    class DoubleStackSize : public Instruction {
    public:
        /**
         * Initailize the double stack size instruction.
         */
        DoubleStackSize();

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

#pragma region DOUBLE_DUMP_STACK
    /**
     * Represents an instruction that dumps the elements of the double stack.
     */
    class DoubleDumpStack : public Instruction {
    public:
        /**
         * Initialize the double stack dump instruction.
         */
        DoubleDumpStack();

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

#pragma region DOUBLE_CLEAR_STACK
    /**
     * Represents an instruction that clears the double stack.
     */
    class DoubleClearStack : public Instruction {
    public:
        /**
         * Initialize the double stack clear instruction.
         */
        DoubleClearStack();

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

#pragma region DOUBLE_POP_STACK
    /**
     * Represents an instruction that removes an double from the stack.
     */
    class DoublePopStack : public Instruction {
    public:
        /**
         * Initialize the double pop instruction.
         */
        DoublePopStack();

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

#pragma region DOUBLE_DUPLICATE_STACK
    /**
     * Represents an instruction that duplicates an double on the stack.
     */
    class DoubleDuplicateStack : public Instruction {
    private:
        /**
         * The number of times the double should be duplicated.
         */
        uint count = 1;

    public:
        /**
         * Initialize the double duplicate instruction.
         */
        DoubleDuplicateStack();

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