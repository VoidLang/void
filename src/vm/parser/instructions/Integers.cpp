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

#pragma region INTEGER_LOAD
    /**
     * Initialize the integer load instruction.
     */
    IntegerLoad::IntegerLoad()
        : Instruction(Instructions::INTEGER_LOAD)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void IntegerLoad::parse(String data, List<String> args, uint line, Executable* executable) {
        // try to parse the storage index from string
        try {
            index = stringToInt(args[0]);
        }
        // get the section index from variable name 
        catch (...) {
            index = executable->getLinker(args[0]);
        }
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerLoad::execute(Context* context) {
        // load the value from the given storage slot
        // and push it to the stack
        context->stack->ints.push(context->storage->ints.get(index));
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerLoad::debug() {
        return "iload " + toString(index);
    }
#pragma endregion

#pragma region INTEGER_STORE
    /**
     * Initialize the integer store instruction.
     */
    IntegerStore::IntegerStore()
        : Instruction(Instructions::INTEGER_STORE)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void IntegerStore::parse(String data, List<String> args, uint line, Executable* executable) {
        // try to parse the storage index from string
        try {
            index = stringToInt(args[0]);
        }
        // get the section index from variable name 
        catch (...) {
            index = executable->getLinker(args[0]);
        }
        // loop through the instruction flags
        for (uint i = 1; i < args.size(); i++) {
            String flag = args[i];
            // check if the instruction should keep the value on the stack
            if (flag == "-k")
                keepStack = true;
        }
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerStore::execute(Context* context) {
        // load the value from the stack
        // and store it in the storage
        context->storage->ints.set(index, context->stack->ints.pull(keepStack));
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerStore::debug() {
        String result = "istore " + toString(index);
        if (keepStack)
            result += " -k";
        return result;
    }
#pragma endregion

#pragma region INTEGER_SET
    /**
     * Initialize the integer set instruction.
     */
    IntegerSet::IntegerSet()
        : Instruction(Instructions::INTEGER_SET)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void IntegerSet::parse(String data, List<String> args, uint line, Executable* executable) {
        // try to parse the storage index from string
        try {
            index = stringToInt(args[0]);
        }
        // get the section index from variable name 
        catch (...) {
            index = executable->getLinker(args[0]);
        }
        // parse the integer value to be pushed to the stack
        value = stringToInt(args[1]);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerSet::execute(Context* context) {
        context->storage->ints.set(index, value);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerSet::debug() {
        return "iset " + toString(index) + " " + toString(value);
    }
#pragma endregion

#pragma region INTEGER_ENSURE
    /**
     * Initialize the integer ensure instruction.
     */
    IntegerEnsure::IntegerEnsure()
        : Instruction(Instructions::INTEGER_ENSURE)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void IntegerEnsure::parse(String data, List<String> args, uint line, Executable* executable) {
        // parse the integer storage required size
        size = stringToInt(args[0]);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerEnsure::execute(Context* context) {
        context->storage->ensure(StorageUnit::INT, size);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerEnsure::debug() {
        return "iensure " + toString(size);
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
            String flag = args[i];
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
        int value =context->stack->ints.pull(keepStack);
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