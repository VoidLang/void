#include "Integers.hpp"

namespace Void {
#pragma region INTEGER_PUSH
    /**
     * Initialize the integer push instruction.
     */
    IntegerPush::IntegerPush()
        : Instruction(Instructions::INTEGER_PUSH)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void IntegerPush::parse(String data, List<String> args, uint line, Executable* executable) {
        // parse the integer value to be pushed to the stack
        value = stringToInt(args[0]);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerPush::execute(Context* context) {
        // pust the integer value to the stack
        context->stack->ints.push(value);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerPush::debug() {
        return "ipush " + toString(value);
    }
#pragma endregion
}