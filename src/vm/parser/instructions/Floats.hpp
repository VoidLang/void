#pragma once

#include "../Instruction.hpp"

#ifdef VOID_INSTRUCTION
namespace Void {
#pragma region FLOAT_PUSH
    /**
     * Represents an instruction that pushes an float to the stack.
     */
    class FloatPush : public Instruction {
    private:
        /**
         * The value to push to the stack.
         */
        float value = 0;

    public:
        /**
         * Initialize the float push instruction.
         */
        FloatPush();

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

#pragma region FLOAT_LOAD
    /**
     * Represents an instruction that loads an float from the storage.
     */
    class FloatLoad : public Instruction {
    private:
        /**
         * The storage index to load the float from.
         */
        uint index = 0;

    public:
        /**
         * Initialize the float load instruction.
         */
        FloatLoad();

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

#pragma region FLOAT_STORE
    /**
     * Represents an instruction that stores an float in the storage.
     */
    class FloatStore : public Instruction {
    private:
        /**
         * The storage index to store the float floato.
         */
        uint index = 0;

        /**
         * Determine if the value should be kept on the stack.
         */
        bool keepStack = false;

    public:
        /**
         * Initialize the float store instruction.
         */
        FloatStore();

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

#pragma region FLOAT_SET
    /**
     * Set the value of the given local variable.
     */
    class FloatSet : public Instruction {
    private:
        /**
         * The local variable storage index to be assigned.
         */
        uint index = 0;

        /**
         * The value to push to be assigned for the variable.
         */
        float value = 0;

    public:
        /**
         * Initialize the float set instruction.
         */
        FloatSet();

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

#pragma region FLOAT_ENSURE
    /**
     * Ensure the capacity of the float variable storage.
     */
    class FloatEnsure : public Instruction {
    private:
        /**
         * The ensured size of the variable storage.
         */
        uint size = 0;

    public:
        /**
         * Initialize the float ensure instruction.
         */
        FloatEnsure();

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

#pragma region FLOAT_ADD
    /**
     * Represents an instruction that adds two float values.
     */
    class FloatAdd : public Instruction {
    private:
        /**
         * The target of te first number in the addition.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        float firstValue = 0;

        /**
         * Determine if the second number should be loaded from the stack.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        float secondValue = 0;

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
         * Initialize the float add instruction.
         */
        FloatAdd();

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

#pragma region FLOAT_SUBTRACT
    /**
     * Represents an instruction that subtracts two float values.
     */
    class FloatSubtract : public Instruction {
    private:
        /**
         * The target of te first number in the subtraction.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        float firstValue = 0;

        /**
         * Determine if the second number should be loaded from the stack.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        float secondValue = 0;

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
         * Initialize the float subtract instruction.
         */
        FloatSubtract();

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

#pragma region FLOAT_MULTIPLY
    /**
     * Represents an instruction that multiplies two float values.
     */
    class FloatMultiply : public Instruction {
    private:
        /**
         * The target of te first number in the multiplication.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        float firstValue = 0;

        /**
         * Determine if the second number should be loaded from the stack.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        float secondValue = 0;

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
         * Initialize the float multiply instruction.
         */
        FloatMultiply();

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

#pragma region FLOAT_DIVIDE
    /**
     * Represents an instruction that divides two float values.
     */
    class FloatDivide : public Instruction {
    private:
        /**
         * The target of te first number in the division.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        float firstValue = 0;

        /**
         * Determine if the second number should be loaded from the stack.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        float secondValue = 0;

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
         * Initialize the float divide instruction.
         */
        FloatDivide();

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

#pragma region FLOAT_MODULO
    /**
     * Represents an instruction that divides two float values and results the remainder.
     */
    class FloatModulo : public Instruction {
    private:
        /**
         * The target of the first number in the remainder division.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        float firstValue = 0;

        /**
         * Determine if the second number should be loaded from the stack.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        float secondValue = 0;

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
         * Initialize the float modulo instruction.
         */
        FloatModulo();

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

#pragma region FLOAT_INCREMENT
    /**
     * Represents an instruction that increments an float by one.
     */
    class FloatIncrement : public Instruction {
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
         * Initialize the float increment instruction.
         */
        FloatIncrement();

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

#pragma region FLOAT_DECREMENT
    /**
     * Represents an instruction that decrements an float by one.
     */
    class FloatDecrement : public Instruction {
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
         * Initialize the float decrement instruction.
         */
        FloatDecrement();

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

#pragma region FLOAT_NEGATE
    /**
     * Represents an instruction that negates an float.
     */
    class FloatNegate : public Instruction {
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
         * Initialize the float negate instruction.
         */
        FloatNegate();

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

#pragma region FLOAT_DEBUG
    /**
     * Represents an instruction that float:prs an float value from the stack.
     */
    class FloatDebug : public Instruction {
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
         * Initailize the float debug instruction.
         */
        FloatDebug();

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

#pragma region FLOAT_IF_EQUALS
    /**
     * Represents an instruction that jumps to a given section if two floats are equal.
     */
    class FloatEquals : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        float firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        float secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the float equals check instruction.
         */
        FloatEquals();

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

#pragma region FLOAT_IF_NOT_EQUALS
    /**
     * Represents an instruction that jumps to a given section if two floats are not equal.
     */
    class FloatNotEquals : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        float firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        float secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the float not equals instruction.
         */
        FloatNotEquals();

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

#pragma region FLOAT_IF_GREATER_THAN
    /**
     * Represents an instruction that jumps to a given section if an float is greater than another.
     */
    class FloatGreaterThan : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        float firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        float secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the float greater than check instruction.
         */
        FloatGreaterThan();

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

#pragma region FLOAT_IF_GREATER_THAN_OR_EQUAL
    /**
     * Represents an instruction that jumps to a given section if an float is greater than or is equal another.
     */
    class FloatGreaterThanOrEquals : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        float firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        float secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the float greater than or equal check instruction.
         */
        FloatGreaterThanOrEquals();

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

#pragma region FLOAT_IF_LESS_THAN
    /**
     * Represents an instruction that jumps to a given section if an float is less than another.
     */
    class FloatLessThan : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        float firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        float secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the float less than check instruction.
         */
        FloatLessThan();

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

#pragma region FLOAT_IF_LESS_THAN_OR_EQUAL
    /**
     * Represents an instruction that jumps to a given section if an float is less than or is equal another.
     */
    class FloatLessThanOrEqual : public Instruction {
    private:
        /**
         * The target of the first number in the check.
         */
        Target firstTarget = Target::STACK;

        /**
         * The storage index or the value of the first number.
         */
        float firstValue = 0;

        /**
         * The target of the second elemnet in the check.
         */
        Target secondTarget = Target::STACK;

        /**
         * The storage index or the value of the second number.
         */
        float secondValue = 0;

        /**
         * The bytecode instruction index to jump to.
         */
        uint index = 0;

    public:
        /**
         * Initialize the float less than or equal check instruction.
         */
        FloatLessThanOrEqual();

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

#pragma region FLOAT_STACK_SIZE
    /**
     * Represents an instruction that retrieves the size of the float stack and pushes the count to the float stack.
     */
    class FloatStackSize : public Instruction {
    public:
        /**
         * Initailize the float stack size instruction.
         */
        FloatStackSize();

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

#pragma region FLOAT_DUMP_STACK
    /**
     * Represents an instruction that dumps the elements of the float stack.
     */
    class FloatDumpStack : public Instruction {
    public:
        /**
         * Initialize the float stack dump instruction.
         */
        FloatDumpStack();

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

#pragma region FLOAT_CLEAR_STACK
    /**
     * Represents an instruction that clears the float stack.
     */
    class FloatClearStack : public Instruction {
    public:
        /**
         * Initialize the float stack clear instruction.
         */
        FloatClearStack();

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

#pragma region FLOAT_POP_STACK
    /**
     * Represents an instruction that removes an float from the stack.
     */
    class FloatPopStack : public Instruction {
    public:
        /**
         * Initialize the float pop instruction.
         */
        FloatPopStack();

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

#pragma region FLOAT_DUPLICATE_STACK
    /**
     * Represents an instruction that duplicates an float on the stack.
     */
    class FloatDuplicateStack : public Instruction {
    private:
        /**
         * The number of times the float should be duplicated.
         */
        uint count = 1;

    public:
        /**
         * Initialize the float duplicate instruction.
         */
        FloatDuplicateStack();

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
