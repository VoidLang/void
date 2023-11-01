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
     * @param executable bytecode executor
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
     * @param executable bytecode executor
     */
    void IntegerLoad::parse(String data, List<String> args, uint line, Executable* executable) {
        // try to parse the storage index from string
        index = executable->getLinker(args[0]);
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
     * @param executable bytecode executor
     */
    void IntegerStore::parse(String data, List<String> args, uint line, Executable* executable) {
        // try to parse the storage index from string
        index = executable->getLinker(args[0]);
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
     * @param executable bytecode executor
     */
    void IntegerSet::parse(String data, List<String> args, uint line, Executable* executable) {
        // try to parse the storage index from string
        index = executable->getLinker(args[0]);
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
     * @param executable bytecode executor
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

#pragma region INTEGER_ADD
    /**
     * Initialize the integer add instruction.
     */
    IntegerAdd::IntegerAdd() 
        : Instruction(Instructions::INTEGER_ADD)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void IntegerAdd::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = executable->getLinker(args[++i]);
                }
            }
            // handle value from the stack
            else if (arg == "-s" || arg == "-stack") {
                if (firstVariable) {
                    firstTarget = Target::STACK;
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::STACK;
                }
            }
            // handle const value
            else if (arg == "-c" || arg == "-const") {
                if (firstVariable) {
                    firstTarget = Target::CONSTANT;
                    firstValue = stringToInt(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToInt(args[++i]);
                }
            }
            // handle addition result
            else if (arg == "-r" || arg == "-result") {
                resultTarget = Target::LOCAL;
                resultLocalIndex = executable->getLinker(args[++i]);
            }
        }
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerAdd::execute(Context* context) {
        // get the first value to be added
        int first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                first = context->storage->ints.get(firstValue);
                break;
        }
        // get the second value to be added
        int second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                second = context->storage->ints.get(secondValue);
                break;
        }
        // add those two numbers
        int result = first + second;
        switch (resultTarget) {
            case Target::STACK:
                context->stack->ints.push(result);
                break;
            case Target::LOCAL:
                context->storage->ints.set(resultLocalIndex, result);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerAdd::debug() {
        String result = "iadd";
        switch (firstTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(firstValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(firstValue);
                break;
        }
        switch (secondTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(secondValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(secondValue);
                break;
        }
        if (resultTarget == Target::LOCAL)
            result += " -r " + toString(resultLocalIndex);
        return result;
    }
#pragma endregion

#pragma region INTEGER_SUBTRACT
    /**
     * Initialize the integer subtract instruction.
     */
    IntegerSubtract::IntegerSubtract()
        : Instruction(Instructions::INTEGER_SUBTRACT)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void IntegerSubtract::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = executable->getLinker(args[++i]);
                }
            }
            // handle value from the stack
            else if (arg == "-s" || arg == "-stack") {
                if (firstVariable) {
                    firstTarget = Target::STACK;
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::STACK;
                }
            }
            // handle const value
            else if (arg == "-c" || arg == "-const") {
                if (firstVariable) {
                    firstTarget = Target::CONSTANT;
                    firstValue = stringToInt(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToInt(args[++i]);
                }
            }
            // handle addition result
            else if (arg == "-r" || arg == "-result") {
                resultTarget = Target::LOCAL;
                resultLocalIndex = executable->getLinker(args[++i]);
            }
        }
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerSubtract::execute(Context* context) {
        // get the first value to be added
        int first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                first = context->storage->ints.get(firstValue);
                break;
        }
        // get the second value to be added
        int second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                second = context->storage->ints.get(secondValue);
                break;
        }
        // add those two numbers
        int result = first - second;
        switch (resultTarget) {
            case Target::STACK:
                context->stack->ints.push(result);
                break;
            case Target::LOCAL:
                context->storage->ints.set(resultLocalIndex, result);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerSubtract::debug() {
        String result = "isub";
        switch (firstTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(firstValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(firstValue);
                break;
        }
        switch (secondTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(secondValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(secondValue);
                break;
        }
        if (resultTarget == Target::LOCAL)
            result += " -r " + toString(resultLocalIndex);
        return result;
    }
#pragma endregion

#pragma region INTEGER_MULTIPLY
    /**
     * Initialize the integer subtract instruction.
     */
    IntegerMultiply::IntegerMultiply()
        : Instruction(Instructions::INTEGER_MULTIPLY)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void IntegerMultiply::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = executable->getLinker(args[++i]);
                }
            }
            // handle value from the stack
            else if (arg == "-s" || arg == "-stack") {
                if (firstVariable) {
                    firstTarget = Target::STACK;
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::STACK;
                }
            }
            // handle const value
            else if (arg == "-c" || arg == "-const") {
                if (firstVariable) {
                    firstTarget = Target::CONSTANT;
                    firstValue = stringToInt(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToInt(args[++i]);
                }
            }
            // handle addition result
            else if (arg == "-r" || arg == "-result") {
                resultTarget = Target::LOCAL;
                resultLocalIndex = executable->getLinker(args[++i]);
            }
        }
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerMultiply::execute(Context* context) {
        // get the first value to be added
        int first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                first = context->storage->ints.get(firstValue);
                break;
            }
        // get the second value to be added
        int second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                second = context->storage->ints.get(secondValue);
                break;
            }
        // add those two numbers
        int result = first * second;
        switch (resultTarget) {
            case Target::STACK:
                context->stack->ints.push(result);
                break;
            case Target::LOCAL:
                context->storage->ints.set(resultLocalIndex, result);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerMultiply::debug() {
        String result = "imul";
        switch (firstTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(firstValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(firstValue);
                break;
        }
        switch (secondTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(secondValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(secondValue);
                break;
        }
        if (resultTarget == Target::LOCAL)
            result += " -r " + toString(resultLocalIndex);
        return result;
    }
#pragma endregion

#pragma region INTEGER_DIVIDE
    /**
     * Initialize the integer divide instruction.
     */
    IntegerDivide::IntegerDivide()
        : Instruction(Instructions::INTEGER_DIVIDE)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void IntegerDivide::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = executable->getLinker(args[++i]);
                }
            }
            // handle value from the stack
            else if (arg == "-s" || arg == "-stack") {
                if (firstVariable) {
                    firstTarget = Target::STACK;
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::STACK;
                }
            }
            // handle const value
            else if (arg == "-c" || arg == "-const") {
                if (firstVariable) {
                    firstTarget = Target::CONSTANT;
                    firstValue = stringToInt(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToInt(args[++i]);
                }
            }
            // handle addition result
            else if (arg == "-r" || arg == "-result") {
                resultTarget = Target::LOCAL;
                resultLocalIndex = executable->getLinker(args[++i]);
            }
        }
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerDivide::execute(Context* context) {
        // get the first value to be added
        int first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                first = context->storage->ints.get(firstValue);
                break;
        }
        // get the second value to be added
        int second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                second = context->storage->ints.get(secondValue);
                break;
        }
        // add those two numbers
        int result = first / second;
        switch (resultTarget) {
            case Target::STACK:
                context->stack->ints.push(result);
                break;
            case Target::LOCAL:
                context->storage->ints.set(resultLocalIndex, result);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerDivide::debug() {
        String result = "idiv";
        switch (firstTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(firstValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(firstValue);
                break;
        }
        switch (secondTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(secondValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(secondValue);
                break;
        }
        if (resultTarget == Target::LOCAL)
            result += " -r " + toString(resultLocalIndex);
        return result;
    }
#pragma endregion

#pragma region INTEGER_MODULO
    /**
     * Initialize the integer modulo instruction.
     */
    IntegerModulo::IntegerModulo()
        : Instruction(Instructions::INTEGER_MODULO)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void IntegerModulo::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = executable->getLinker(args[++i]);
                }
            }
            // handle value from the stack
            else if (arg == "-s" || arg == "-stack") {
                if (firstVariable) {
                    firstTarget = Target::STACK;
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::STACK;
                }
            }
            // handle const value
            else if (arg == "-c" || arg == "-const") {
                if (firstVariable) {
                    firstTarget = Target::CONSTANT;
                    firstValue = stringToInt(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToInt(args[++i]);
                }
            }
            // handle addition result
            else if (arg == "-r" || arg == "-result") {
                resultTarget = Target::LOCAL;
                resultLocalIndex = executable->getLinker(args[++i]);
            }
        }
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerModulo::execute(Context* context) {
        // get the first value to be added
        int first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                first = context->storage->ints.get(firstValue);
                break;
        }
        // get the second value to be added
        int second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                second = context->storage->ints.get(secondValue);
                break;
        }
        // add those two numbers
        int result = first % second;
        switch (resultTarget) {
            case Target::STACK:
                context->stack->ints.push(result);
                break;
            case Target::LOCAL:
                context->storage->ints.set(resultLocalIndex, result);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerModulo::debug() {
        String result = "imod";
        switch (firstTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(firstValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(firstValue);
                break;
        }
        switch (secondTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(secondValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(secondValue);
                break;
        }
        if (resultTarget == Target::LOCAL)
            result += " -r " + toString(resultLocalIndex);
        return result;
    }
#pragma endregion

#pragma region INTEGER_INCREMENT
    /**
     * Initialize the integer increment instruction.
     */
    IntegerIncrement::IntegerIncrement()
        : Instruction(Instructions::INTEGER_INCREMENT)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void IntegerIncrement::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void IntegerIncrement::execute(Context* context) {
        // get the value to be incremented
        int value = 0;
        switch (source) {
            case Target::STACK:
                value = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                value = context->storage->ints.get(sourceIndex);
                break;
        }
        // increment the value
        value++;
        switch (result) {
            case Target::STACK:
                context->stack->ints.push(value);
                break;
            case Target::LOCAL:
                context->storage->ints.set(resultIndex, value);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerIncrement::debug() {
        String debug = "iinc";
        switch (source) {
            case Target::STACK:
                debug += " -stack";
                break;
            case Target::LOCAL:
                debug += " -local " + toString(sourceIndex);
                break;
        }
        switch (result) {
            case Target::LOCAL:
                debug += " -result " + toString(resultIndex);
        }
        return debug;
    }
#pragma endregion

#pragma region INTEGER_DECREMENT
    /**
     * Initialize the integer decrement instruction.
     */
    IntegerDecrement::IntegerDecrement()
        : Instruction(Instructions::INTEGER_DECREMENT)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void IntegerDecrement::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void IntegerDecrement::execute(Context* context) {
        // get the value to be incremented
        int value = 0;
        switch (source) {
            case Target::STACK:
                value = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                value = context->storage->ints.get(sourceIndex);
                break;
        }
        // increment the value
        value--;
        switch (result) {
            case Target::STACK:
                context->stack->ints.push(value);
                break;
            case Target::LOCAL:
                context->storage->ints.set(resultIndex, value);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerDecrement::debug() {
        String debug = "idecr";
        switch (source) {
            case Target::STACK:
                debug += " -stack";
                break;
            case Target::LOCAL:
                debug += " -local " + toString(sourceIndex);
                break;
        }
        switch (result) {
            case Target::LOCAL:
                debug += " -result " + toString(resultIndex);
            }
        return debug;
    }
#pragma endregion

#pragma region INTEGER_NEGATE
    /**
     * Initialize the integer negate instruction.
     */
    IntegerNegate::IntegerNegate()
        : Instruction(Instructions::INTEGER_NEGATE)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void IntegerNegate::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void IntegerNegate::execute(Context* context) {
        // get the value to be incremented
        int value = 0;
        switch (source) {
            case Target::STACK:
                value = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                value = context->storage->ints.get(sourceIndex);
                break;
        }
        // negate the value
        value = -value;
        switch (result) {
            case Target::STACK:
                context->stack->ints.push(value);
                break;
            case Target::LOCAL:
                context->storage->ints.set(resultIndex, value);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerNegate::debug() {
        String debug = "ineg";
        switch (source) {
            case Target::STACK:
                debug += " -stack";
                break;
            case Target::LOCAL:
                debug += " -local " + toString(sourceIndex);
                break;
        }
        switch (result) {
            case Target::LOCAL:
                debug += " -result " + toString(resultIndex);
        }
        return debug;
    }
#pragma endregion

#pragma region INTEGER_RETURN
    /**
     * Initialize the integer return instruction.
     */
    IntegerReturn::IntegerReturn()
        : Instruction(Instructions::INTEGER_RETURN)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void IntegerReturn::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                source = Target::LOCAL;
                sourceValue = executable->getLinker(args[++i]);
            }
            // handle constant value
            else if (arg == "-c" || arg == "-const") {
                source = Target::CONSTANT;
                sourceValue = stringToInt(args[++i]);
            }
        }
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerReturn::execute(Context* context) {
        // get the value to be incremented
        int value = sourceValue;
        switch (source) {
            case Target::STACK:
                value = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                value = context->storage->ints.get((uint) sourceValue);
                break;
        }
        // terminate the execution and set the return value
        context->terminate(value);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerReturn::debug() {
        String result = "ireturn";
        switch (source) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(sourceValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(sourceValue);
                break;
        }
        return result;
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
     * @param executable bytecode executor
     */
    void IntegerDebug::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the debug flags
        for (uint i = 0; i < args.size(); i++) {
            String flag = args[i];
            // check if the debug should insert a new line afterwards
            if (flag == "-n" || flag == "-new" || flag == "-newline" || flag == "-nl")
                newLine = true;
            // check if the value should be kept on the stack
            else if (flag == "-k" || flag == "-keep" || flag == "-keepstack")
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
            result += " -newline";
        if (keepStack)
            result += " -keepstack";
        return result;
    }
#pragma endregion

#pragma region INTEGER_IF_EQUALS
    /**
         * Initialize the integer equals check instruction.
         */
    IntegerEquals::IntegerEquals()
        : Instruction(Instructions::INTEGER_IF_EQUAL)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void IntegerEquals::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = executable->getLinker(args[++i]);
                }
            }
            // handle value from the stack
            else if (arg == "-s" || arg == "-stack") {
                if (firstVariable) {
                    firstTarget = Target::STACK;
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::STACK;
                }
            }
            // handle const value
            else if (arg == "-c" || arg == "-const") {
                if (firstVariable) {
                    firstTarget = Target::CONSTANT;
                    firstValue = stringToInt(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToInt(args[++i]);
                }
            }
            // handle addition result
            else if (arg == "-j" || arg == "-jump")
                index = executable->getSection(args[++i]);
        }
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerEquals::execute(Context* context) {
        // get the first value to be added
        int first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                first = context->storage->ints.get(firstValue);
                break;
        }
        // get the second value to be added
        int second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                second = context->storage->ints.get(secondValue);
                break;
        }
        // check if the two numbers equal
        if (first == second)
            context->cursor = index;
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerEquals::debug() {
        String result = "ifi==";
        switch (firstTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(firstValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(firstValue);
                break;
        }
        switch (secondTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(secondValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(secondValue);
                break;
        }
        return result + " -jump " + toString(index);
    }
#pragma endregion

#pragma region INTEGER_IF_NOT_EQUALS
    /**
     * Initialize the integer not equals instruction.
     */
    IntegerNotEquals::IntegerNotEquals()
        : Instruction(Instructions::INTEGER_IF_NOT_EQUAL)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void IntegerNotEquals::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = executable->getLinker(args[++i]);
                }
            }
            // handle value from the stack
            else if (arg == "-s" || arg == "-stack") {
                if (firstVariable) {
                    firstTarget = Target::STACK;
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::STACK;
                }
            }
            // handle const value
            else if (arg == "-c" || arg == "-const") {
                if (firstVariable) {
                    firstTarget = Target::CONSTANT;
                    firstValue = stringToInt(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToInt(args[++i]);
                }
            }
            // handle addition result
            else if (arg == "-j" || arg == "-jump")
                index = executable->getSection(args[++i]);
        }
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerNotEquals::execute(Context* context) {
        // get the first value to be added
        int first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                first = context->storage->ints.get(firstValue);
                break;
        }
        // get the second value to be added
        int second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                second = context->storage->ints.get(secondValue);
                break;
        }
        // check if the two numbers equal
        if (first != second)
            context->cursor = index;
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerNotEquals::debug() {
        String result = "ifi!=";
        switch (firstTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(firstValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(firstValue);
                break;
        }
        switch (secondTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(secondValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(secondValue);
                break;
        }
        return result + " -jump " + toString(index);
    }
#pragma endregion

#pragma region INTEGER_IF_GREATER_THAN
    /**
     * Initialize the integer greater than check instruction.
     */
    IntegerGreaterThan::IntegerGreaterThan()
        : Instruction(Instructions::INTEGER_IF_GREATER_THAN)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void IntegerGreaterThan::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = executable->getLinker(args[++i]);
                }
            }
            // handle value from the stack
            else if (arg == "-s" || arg == "-stack") {
                if (firstVariable) {
                    firstTarget = Target::STACK;
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::STACK;
                }
            }
            // handle const value
            else if (arg == "-c" || arg == "-const") {
                if (firstVariable) {
                    firstTarget = Target::CONSTANT;
                    firstValue = stringToInt(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToInt(args[++i]);
                }
            }
            // handle addition result
            else if (arg == "-j" || arg == "-jump")
                index = executable->getSection(args[++i]);
        }
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerGreaterThan::execute(Context* context) {
        // get the first value to be added
        int first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                first = context->storage->ints.get(firstValue);
                break;
        }
        // get the second value to be added
        int second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                second = context->storage->ints.get(secondValue);
                break;
        }
        // check if the two numbers equal
        if (first > second)
            context->cursor = index;
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerGreaterThan::debug() {
        String result = "ifi>";
        switch (firstTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(firstValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(firstValue);
                break;
        }
        switch (secondTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(secondValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(secondValue);
                break;
        }
        return result + " -jump " + toString(index);
    }
#pragma endregion

#pragma region INTEGER_IF_GREATER_THAN_OR_EQUAL
    /**
     * Initialize the integer greater than check instruction.
     */
    IntegerGreaterThanOrEquals::IntegerGreaterThanOrEquals()
        : Instruction(Instructions::INTEGER_IF_GREATER_THAN_OR_EQUAL)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void IntegerGreaterThanOrEquals::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = executable->getLinker(args[++i]);
                }
            }
            // handle value from the stack
            else if (arg == "-s" || arg == "-stack") {
                if (firstVariable) {
                    firstTarget = Target::STACK;
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::STACK;
                }
            }
            // handle const value
            else if (arg == "-c" || arg == "-const") {
                if (firstVariable) {
                    firstTarget = Target::CONSTANT;
                    firstValue = stringToInt(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToInt(args[++i]);
                }
            }
            // handle addition result
            else if (arg == "-j" || arg == "-jump")
                index = executable->getSection(args[++i]);
        }
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerGreaterThanOrEquals::execute(Context* context) {
        // get the first value to be added
        int first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                first = context->storage->ints.get(firstValue);
                break;
        }
        // get the second value to be added
        int second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                second = context->storage->ints.get(secondValue);
                break;
        }
        // check if the two numbers equal
        if (first >= second)
            context->cursor = index;
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerGreaterThanOrEquals::debug() {
        String result = "ifi>=";
        switch (firstTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(firstValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(firstValue);
                break;
        }
        switch (secondTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(secondValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(secondValue);
                break;
        }
        return result + " -jump " + toString(index);
    }
#pragma endregion

#pragma region INTEGER_IF_LESS_THAN
    /**
     * Initialize the integer less than check instruction.
     */
    IntegerLessThan::IntegerLessThan()
        : Instruction(Instructions::INTEGER_IF_LESS_THAN)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void IntegerLessThan::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = executable->getLinker(args[++i]);
                }
            }
            // handle value from the stack
            else if (arg == "-s" || arg == "-stack") {
                if (firstVariable) {
                    firstTarget = Target::STACK;
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::STACK;
                }
            }
            // handle const value
            else if (arg == "-c" || arg == "-const") {
                if (firstVariable) {
                    firstTarget = Target::CONSTANT;
                    firstValue = stringToInt(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToInt(args[++i]);
                }
            }
            // handle addition result
            else if (arg == "-j" || arg == "-jump")
                index = executable->getSection(args[++i]);
        }
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerLessThan::execute(Context* context) {
        // get the first value to be added
        int first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                first = context->storage->ints.get(firstValue);
                break;
        }
        // get the second value to be added
        int second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                second = context->storage->ints.get(secondValue);
                break;
        }
        // check if the two numbers equal
        if (first < second)
            context->cursor = index;
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerLessThan::debug() {
        String result = "ifi<";
        switch (firstTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(firstValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(firstValue);
                break;
        }
        switch (secondTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(secondValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(secondValue);
                break;
        }
        return result + " -jump " + toString(index);
    }
#pragma endregion

#pragma region INTEGER_IF_LESS_THAN_OR_EQUAL
    /**
     * Initialize the integer less than check instruction.
     */
    IntegerLessThanOrEqual::IntegerLessThanOrEqual()
        : Instruction(Instructions::INTEGER_IF_LESS_THAN_OR_EQUAL)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void IntegerLessThanOrEqual::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = executable->getLinker(args[++i]);
                }
            }
            // handle value from the stack
            else if (arg == "-s" || arg == "-stack") {
                if (firstVariable) {
                    firstTarget = Target::STACK;
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::STACK;
                }
            }
            // handle const value
            else if (arg == "-c" || arg == "-const") {
                if (firstVariable) {
                    firstTarget = Target::CONSTANT;
                    firstValue = stringToInt(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToInt(args[++i]);
                }
            }
            // handle addition result
            else if (arg == "-j" || arg == "-jump")
                index = executable->getSection(args[++i]);
        }
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerLessThanOrEqual::execute(Context* context) {
        // get the first value to be added
        int first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                first = context->storage->ints.get(firstValue);
                break;
        }
        // get the second value to be added
        int second = secondValue;
            switch (secondTarget) {
            case Target::STACK:
                second = context->stack->ints.pull();
                break;
            case Target::LOCAL:
                second = context->storage->ints.get(secondValue);
                break;
        }
        // check if the two numbers equal
        if (first <= second)
            context->cursor = index;
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerLessThanOrEqual::debug() {
        String result = "ifi<=";
        switch (firstTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(firstValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(firstValue);
                break;
        }
        switch (secondTarget) {
            case Target::STACK:
                result += " -stack";
                break;
            case Target::LOCAL:
                result += " -local " + toString(secondValue);
                break;
            case Target::CONSTANT:
                result += " -const " + toString(secondValue);
                break;
        }
        return result + " -jump " + toString(index);
    }
#pragma endregion

#pragma region INTEGER_STACK_SIZE
    /**
     * Initailize the integer stack size instruction.
     */
    IntegerStackSize::IntegerStackSize() 
        : Instruction(Instructions::INTEGER_STACK_SIZE) 
    { }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerStackSize::execute(Context* context) {
        context->stack->ints.push(context->stack->ints.size());
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerStackSize::debug() {
        return "istacksize";
    }
#pragma endregion

#pragma region INTEGER_DUMP_STACK
    /**
     * Initialize the integer stack dump instruction.
     */
    IntegerDumpStack::IntegerDumpStack()
        : Instruction(Instructions::INTEGER_DUMP_STACK)
    { }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerDumpStack::execute(Context* context) {
        uint size = context->stack->ints.size();;
        println("[log] int stack dump (" << size << ")");
        for (uint i = 0; i < size; i++) {
            println("- " << context->stack->ints.at(i) << " [" << i << "]");
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerDumpStack::debug() {
        return "idumpstack";
    }
#pragma endregion

#pragma region INTEGER_CLEAR_STACK
    /**
     * Initialize the integer stack clear instruction.
     */
    IntegerClearStack::IntegerClearStack()
        : Instruction(Instructions::INTEGER_CLEAR_STACK)
    { }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerClearStack::execute(Context* context) {
        context->stack->ints.clear();
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerClearStack::debug() {
        return "iclearstack";
    }
#pragma endregion

#pragma region INTEGER_POP_STACK
    /**
     * Initialize the integer pop instruction.
     */
    IntegerPopStack::IntegerPopStack()
        : Instruction(Instructions::INTEGER_POP_STACK)
    { }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerPopStack::execute(Context* context) {
        context->stack->ints.pull();
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerPopStack::debug() {
        return "ipop";
    }
#pragma endregion

#pragma region INTEGER_DUPLICATE_STACK
    /**
     * Initialize the integer duplicate instruction.
     */
    IntegerDuplicateStack::IntegerDuplicateStack()
        : Instruction(Instructions::INTEGER_DUPLICATE_STACK)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void IntegerDuplicateStack::parse(String data, List<String> args, uint line, Executable* executable) {
        // parse the duplication count
        if (!args.empty())
            count = stringToInt(args[0]);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void IntegerDuplicateStack::execute(Context* context) {
        // get the value to be duplicated without being removed
        int value = context->stack->ints.get();
        // push the value to the stack the given times
        for (uint i = 0; i < count; i++)
            context->stack->ints.push(value);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String IntegerDuplicateStack::debug() {
        String result = "idup";
        if (count > 1)
            result += " " + toString(count);
        return result;
    }
#pragma endregion
}