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

#pragma region INTEGER_DEBUG
    /**
     * Initailize the integer debug instruction.
     */
    IntegerDebug::IntegerDebug()
        : Instruction(Instructions::INTEGER_DEBUG)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void IntegerDebug::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the debug flags
        for (uint i = 0; i < args.size(); i++) {
            String flag = args[1];
            // check if the debug should insert a new line afterwards
            if (flag == "-n")
                newLine = true;
            // check if the value should be kept on the stack
            else if (flag == "-k")
                keepStack = true;
        }
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerDebug::execute(Context* context) {
        // get the value from the stack
        int value = keepStack ? context->stack->ints.get() : context->stack->ints.pull();
        // print the value and insert a new line if the flag is set
        print(value);
        if (newLine)
            println("");
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerDebug::debug() {
        String result = "idebug";
        if (newLine)
            result += " -n";
        if (keepStack)
            result += " -k";
        return result;
    }
#pragma endregion
}