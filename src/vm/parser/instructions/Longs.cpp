#include "Longs.hpp"

namespace Void {
#pragma region LONG_PUSH
    /**
     * Initialize the long push instruction.
     */
    LongPush::LongPush()
        : Instruction(Instructions::LONG_PUSH)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongPush::parse(String data, List<String> args, uint line, Executable* executable) {
        // parse the long value to be pushed to the stack
        value = stringToInt(args[0]);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void LongPush::execute(Context* context) {
        // pust the long value to the stack
        context->stack->longs.push(value);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String LongPush::debug() {
        return "ipush " + toString(value);
    }
#pragma endregion

#pragma region LONG_LOAD
    /**
     * Initialize the long load instruction.
     */
    LongLoad::LongLoad()
        : Instruction(Instructions::LONG_LOAD)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongLoad::parse(String data, List<String> args, uint line, Executable* executable) {
        // try to parse the storage index from string
        index = executable->getLinker(args[0]);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void LongLoad::execute(Context* context) {
        // load the value from the given storage slot
        // and push it to the stack
        context->stack->longs.push(context->storage->longs.get(index));
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String LongLoad::debug() {
        return "iload " + toString(index);
    }
#pragma endregion

#pragma region LONG_STORE
    /**
     * Initialize the long store instruction.
     */
    LongStore::LongStore()
        : Instruction(Instructions::LONG_STORE)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongStore::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void LongStore::execute(Context* context) {
        // load the value from the stack
        // and store it in the storage
        context->storage->longs.set(index, context->stack->longs.pull(keepStack));
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String LongStore::debug() {
        String result = "istore " + toString(index);
        if (keepStack)
            result += " -k";
        return result;
    }
#pragma endregion

#pragma region LONG_SET
    /**
     * Initialize the long set instruction.
     */
    LongSet::LongSet()
        : Instruction(Instructions::LONG_SET)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongSet::parse(String data, List<String> args, uint line, Executable* executable) {
        // try to parse the storage index from string
        try {
            index = stringToInt(args[0]);
        }
        // get the section index from variable name 
        catch (...) {
            index = executable->getLinker(args[0]);
        }
        // parse the long value to be pushed to the stack
        value = stringToInt(args[1]);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void LongSet::execute(Context* context) {
        context->storage->longs.set(index, value);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String LongSet::debug() {
        return "iset " + toString(index) + " " + toString(value);
    }
#pragma endregion

#pragma region LONG_ENSURE
    /**
     * Initialize the long ensure instruction.
     */
    LongEnsure::LongEnsure()
        : Instruction(Instructions::LONG_ENSURE)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongEnsure::parse(String data, List<String> args, uint line, Executable* executable) {
        // parse the long storage required size
        size = stringToInt(args[0]);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void LongEnsure::execute(Context* context) {
        context->storage->ensure(StorageUnit::INT, size);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String LongEnsure::debug() {
        return "iensure " + toString(size);
    }
#pragma endregion

#pragma region LONG_ADD
    /**
     * Initialize the long add instruction.
     */
    LongAdd::LongAdd()
        : Instruction(Instructions::LONG_ADD)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongAdd::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void LongAdd::execute(Context* context) {
        // get the first value to be added
        lint first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                first = context->storage->longs.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        lint second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                second = context->storage->longs.get((uint)secondValue);
                break;
        }
        // add those two numbers
        lint result = first + second;
        switch (resultTarget) {
            case Target::STACK:
                context->stack->longs.push(result);
                break;
            case Target::LOCAL:
                context->storage->longs.set(resultLocalIndex, result);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String LongAdd::debug() {
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

#pragma region LONG_SUBTRACT
    /**
     * Initialize the long subtract instruction.
     */
    LongSubtract::LongSubtract()
        : Instruction(Instructions::LONG_SUBTRACT)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongSubtract::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void LongSubtract::execute(Context* context) {
        // get the first value to be added
        lint first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                first = context->storage->longs.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        lint second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                second = context->storage->longs.get((uint) secondValue);
                break;
        }
        // add those two numbers
        lint result = first - second;
        switch (resultTarget) {
            case Target::STACK:
                context->stack->longs.push(result);
                break;
            case Target::LOCAL:
                context->storage->longs.set(resultLocalIndex, result);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String LongSubtract::debug() {
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

#pragma region LONG_MULTIPLY
    /**
     * Initialize the long subtract instruction.
     */
    LongMultiply::LongMultiply()
        : Instruction(Instructions::LONG_MULTIPLY)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongMultiply::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void LongMultiply::execute(Context* context) {
        // get the first value to be added
        lint first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                first = context->storage->longs.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        lint second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                second = context->storage->longs.get((uint) secondValue);
                break;
        }
        // add those two numbers
        lint result = first * second;
        switch (resultTarget) {
            case Target::STACK:
                context->stack->longs.push(result);
                break;
            case Target::LOCAL:
                context->storage->longs.set(resultLocalIndex, result);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String LongMultiply::debug() {
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

#pragma region LONG_DIVIDE
    /**
     * Initialize the long divide instruction.
     */
    LongDivide::LongDivide()
        : Instruction(Instructions::LONG_DIVIDE)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongDivide::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void LongDivide::execute(Context* context) {
        // get the first value to be added
        lint first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                first = context->storage->longs.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        lint second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                second = context->storage->longs.get((uint) secondValue);
                break;
        }
        // add those two numbers
        lint result = first / second;
        switch (resultTarget) {
            case Target::STACK:
                context->stack->longs.push(result);
                break;
            case Target::LOCAL:
                context->storage->longs.set(resultLocalIndex, result);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String LongDivide::debug() {
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

#pragma region LONG_MODULO
    /**
     * Initialize the long modulo instruction.
     */
    LongModulo::LongModulo()
        : Instruction(Instructions::LONG_MODULO)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongModulo::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void LongModulo::execute(Context* context) {
        // get the first value to be added
        lint first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                first = context->storage->longs.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        lint second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                second = context->storage->longs.get((uint) secondValue);
                break;
        }
        // add those two numbers
        lint result = first % second;
        switch (resultTarget) {
            case Target::STACK:
                context->stack->longs.push(result);
                break;
            case Target::LOCAL:
                context->storage->longs.set(resultLocalIndex, result);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String LongModulo::debug() {
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

#pragma region LONG_INCREMENT
    /**
     * Initialize the long increment instruction.
     */
    LongIncrement::LongIncrement()
        : Instruction(Instructions::LONG_INCREMENT)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongIncrement::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void LongIncrement::execute(Context* context) {
        // get the value to be incremented
        lint value = 0;
        switch (source) {
            case Target::STACK:
                value = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                value = context->storage->longs.get(sourceIndex);
                break;
        }
        // increment the value
        value++;
        switch (result) {
            case Target::STACK:
                context->stack->longs.push(value);
                break;
            case Target::LOCAL:
                context->storage->longs.set(resultIndex, value);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String LongIncrement::debug() {
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

#pragma region LONG_DECREMENT
    /**
     * Initialize the long decrement instruction.
     */
    LongDecrement::LongDecrement()
        : Instruction(Instructions::LONG_DECREMENT)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongDecrement::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void LongDecrement::execute(Context* context) {
        // get the value to be incremented
        lint value = 0;
        switch (source) {
            case Target::STACK:
                value = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                value = context->storage->longs.get(sourceIndex);
                break;
        }
        // increment the value
        value--;
        switch (result) {
            case Target::STACK:
                context->stack->longs.push(value);
                break;
            case Target::LOCAL:
                context->storage->longs.set(resultIndex, value);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String LongDecrement::debug() {
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

#pragma region LONG_NEGATE
    /**
     * Initialize the long negate instruction.
     */
    LongNegate::LongNegate()
        : Instruction(Instructions::LONG_NEGATE)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongNegate::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void LongNegate::execute(Context* context) {
        // get the value to be incremented
        lint value = 0;
        switch (source) {
            case Target::STACK:
                value = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                value = context->storage->longs.get(sourceIndex);
                break;
        }
        // negate the value
        value = -value;
        switch (result) {
            case Target::STACK:
                context->stack->longs.push(value);
                break;
            case Target::LOCAL:
                context->storage->longs.set(resultIndex, value);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String LongNegate::debug() {
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

#pragma region LONG_DEBUG
    /**
     * Initailize the long debug instruction.
     */
    LongDebug::LongDebug()
        : Instruction(Instructions::LONG_DEBUG)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongDebug::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the debug flags
        for (uint i = 0; i < args.size(); i++) {
            String flag = args[i];
            // check if the debug should insert a new line afterwards
            if (flag == "-n" || flag == "-new" || flag == "-newline" || flag == "-nl")
                newLine = true;
            // check if the value should be kept on the stack
            else if (flag == "-k" || flag == "-kep" || flag == "-keepstack")
                keepStack = true;
        }
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void LongDebug::execute(Context* context) {
        // get the value from the stack
        lint value = context->stack->longs.pull(keepStack);
        // prlint the value and insert a new line if the flag is set
        print(value);
        if (newLine)
            println("");
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String LongDebug::debug() {
        String result = "idebug";
        if (newLine)
            result += " -newline";
        if (keepStack)
            result += " -keepstack";
        return result;
    }
#pragma endregion

#pragma region LONG_IF_EQUALS
    /**
         * Initialize the long equals check instruction.
         */
    LongEquals::LongEquals()
        : Instruction(Instructions::LONG_IF_EQUAL)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongEquals::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void LongEquals::execute(Context* context) {
        // get the first value to be added
        lint first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                first = context->storage->longs.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        lint second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                second = context->storage->longs.get((uint) secondValue);
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
    String LongEquals::debug() {
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

#pragma region LONG_IF_NOT_EQUALS
    /**
     * Initialize the long not equals instruction.
     */
    LongNotEquals::LongNotEquals()
        : Instruction(Instructions::LONG_IF_NOT_EQUAL)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongNotEquals::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void LongNotEquals::execute(Context* context) {
        // get the first value to be added
        lint first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                first = context->storage->longs.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        lint second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                second = context->storage->longs.get((uint) secondValue);
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
    String LongNotEquals::debug() {
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

#pragma region LONG_IF_GREATER_THAN
    /**
     * Initialize the long greater than check instruction.
     */
    LongGreaterThan::LongGreaterThan()
        : Instruction(Instructions::LONG_IF_GREATER_THAN)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongGreaterThan::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void LongGreaterThan::execute(Context* context) {
        // get the first value to be added
        lint first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                first = context->storage->longs.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        lint second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                second = context->storage->longs.get((uint) secondValue);
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
    String LongGreaterThan::debug() {
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

#pragma region LONG_IF_GREATER_THAN_OR_EQUAL
    /**
     * Initialize the long greater than check instruction.
     */
    LongGreaterThanOrEquals::LongGreaterThanOrEquals()
        : Instruction(Instructions::LONG_IF_GREATER_THAN_OR_EQUAL)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongGreaterThanOrEquals::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void LongGreaterThanOrEquals::execute(Context* context) {
        // get the first value to be added
        lint first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                first = context->storage->longs.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        lint second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                second = context->storage->longs.get((uint) secondValue);
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
    String LongGreaterThanOrEquals::debug() {
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

#pragma region LONG_IF_LESS_THAN
    /**
     * Initialize the long less than check instruction.
     */
    LongLessThan::LongLessThan()
        : Instruction(Instructions::LONG_IF_LESS_THAN)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongLessThan::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void LongLessThan::execute(Context* context) {
        // get the first value to be added
        lint first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                first = context->storage->longs.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        lint second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                second = context->storage->longs.get((uint) secondValue);
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
    String LongLessThan::debug() {
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

#pragma region LONG_IF_LESS_THAN_OR_EQUAL
    /**
     * Initialize the long less than check instruction.
     */
    LongLessThanOrEqual::LongLessThanOrEqual()
        : Instruction(Instructions::LONG_IF_LESS_THAN_OR_EQUAL)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongLessThanOrEqual::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void LongLessThanOrEqual::execute(Context* context) {
        // get the first value to be added
        lint first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                first = context->storage->longs.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        lint second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->longs.pull();
                break;
            case Target::LOCAL:
                second = context->storage->longs.get((uint) secondValue);
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
    String LongLessThanOrEqual::debug() {
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

#pragma region LONG_STACK_SIZE
    /**
     * Initailize the long stack size instruction.
     */
    LongStackSize::LongStackSize()
        : Instruction(Instructions::LONG_STACK_SIZE)
    { }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void LongStackSize::execute(Context* context) {
        context->stack->longs.push(context->stack->longs.size());
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String LongStackSize::debug() {
        return "istacksize";
    }
#pragma endregion

#pragma region LONG_DUMP_STACK
    /**
     * Initialize the long stack dump instruction.
     */
    LongDumpStack::LongDumpStack()
        : Instruction(Instructions::LONG_DUMP_STACK)
    { }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void LongDumpStack::execute(Context* context) {
        uint size = context->stack->longs.size();;
        println("[log] lint stack dump (" << size << ")");
        for (uint i = 0; i < size; i++) {
            println("- " << context->stack->longs.at(i) << " [" << i << "]");
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String LongDumpStack::debug() {
        return "idumpstack";
    }
#pragma endregion

#pragma region LONG_CLEAR_STACK
    /**
     * Initialize the long stack clear instruction.
     */
    LongClearStack::LongClearStack()
        : Instruction(Instructions::LONG_CLEAR_STACK)
    { }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void LongClearStack::execute(Context* context) {
        context->stack->longs.clear();
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String LongClearStack::debug() {
        return "iclearstack";
    }
#pragma endregion

#pragma region LONG_POP_STACK
    /**
     * Initialize the long pop instruction.
     */
    LongPopStack::LongPopStack()
        : Instruction(Instructions::LONG_POP_STACK)
    { }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void LongPopStack::execute(Context* context) {
        context->stack->longs.pull();
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String LongPopStack::debug() {
        return "ipop";
    }
#pragma endregion

#pragma region LONG_DUPLICATE_STACK
    /**
     * Initialize the long duplicate instruction.
     */
    LongDuplicateStack::LongDuplicateStack()
        : Instruction(Instructions::LONG_DUPLICATE_STACK)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void LongDuplicateStack::parse(String data, List<String> args, uint line, Executable* executable) {
        // parse the duplication count
        if (!args.empty())
            count = stringToInt(args[0]);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void LongDuplicateStack::execute(Context* context) {
        // get the value to be duplicated without being removed
        lint value = context->stack->longs.get();
        // push the value to the stack the given times
        for (uint i = 0; i < count; i++)
            context->stack->longs.push(value);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String LongDuplicateStack::debug() {
        String result = "idup";
        if (count > 1)
            result += " " + toString(count);
        return result;
    }
#pragma endregion
}
