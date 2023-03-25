#include "Doubles.hpp"

namespace Void {
#pragma region DOUBLE_PUSH
    /**
     * Initialize the double push instruction.
     */
    DoublePush::DoublePush()
        : Instruction(Instructions::DOUBLE_PUSH)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoublePush::parse(String data, List<String> args, uint line, Executable* executable) {
        // parse the double value to be pushed to the stack
        value = stringToDouble(args[0]);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void DoublePush::execute(Context* context) {
        // pust the double value to the stack
        context->stack->doubles.push(value);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String DoublePush::debug() {
        return "dpush " + toString(value);
    }
#pragma endregion

#pragma region DOUBLE_LOAD
    /**
     * Initialize the double load instruction.
     */
    DoubleLoad::DoubleLoad()
        : Instruction(Instructions::DOUBLE_LOAD)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoubleLoad::parse(String data, List<String> args, uint line, Executable* executable) {
        // try to parse the storage index from string
        index = executable->getLinker(args[0]);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void DoubleLoad::execute(Context* context) {
        // load the value from the given storage slot
        // and push it to the stack
        context->stack->doubles.push(context->storage->doubles.get(index));
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String DoubleLoad::debug() {
        return "dload " + toString(index);
    }
#pragma endregion

#pragma region DOUBLE_STORE
    /**
     * Initialize the double store instruction.
     */
    DoubleStore::DoubleStore()
        : Instruction(Instructions::DOUBLE_STORE)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoubleStore::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void DoubleStore::execute(Context* context) {
        // load the value from the stack
        // and store it in the storage
        context->storage->doubles.set(index, context->stack->doubles.pull(keepStack));
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String DoubleStore::debug() {
        String result = "dstore " + toString(index);
        if (keepStack)
            result += " -k";
        return result;
    }
#pragma endregion

#pragma region DOUBLE_SET
    /**
     * Initialize the double set instruction.
     */
    DoubleSet::DoubleSet()
        : Instruction(Instructions::DOUBLE_SET)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoubleSet::parse(String data, List<String> args, uint line, Executable* executable) {
        // try to parse the storage index from string
        try {
            index = stringToInt(args[0]);
        }
        // get the section index from variable name 
        catch (...) {
            index = executable->getLinker(args[0]);
        }
        // parse the double value to be pushed to the stack
        value = stringToDouble(args[1]);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void DoubleSet::execute(Context* context) {
        context->storage->doubles.set(index, value);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String DoubleSet::debug() {
        return "dset " + toString(index) + " " + toString(value);
    }
#pragma endregion

#pragma region DOUBLE_ENSURE
    /**
     * Initialize the double ensure instruction.
     */
    DoubleEnsure::DoubleEnsure()
        : Instruction(Instructions::DOUBLE_ENSURE)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoubleEnsure::parse(String data, List<String> args, uint line, Executable* executable) {
        // parse the double storage required size
        size = stringToInt(args[0]);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void DoubleEnsure::execute(Context* context) {
        context->storage->ensure(StorageUnit::INT, size);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String DoubleEnsure::debug() {
        return "densure " + toString(size);
    }
#pragma endregion

#pragma region DOUBLE_ADD
    /**
     * Initialize the double add instruction.
     */
    DoubleAdd::DoubleAdd()
        : Instruction(Instructions::DOUBLE_ADD)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoubleAdd::parse(String data, List<String> args, uint line, Executable* executable) {
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
                    firstValue = stringToDouble(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToDouble(args[++i]);
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
    void DoubleAdd::execute(Context* context) {
        // get the first value to be added
        double first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                first = context->storage->doubles.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        double second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                second = context->storage->doubles.get((uint) secondValue);
                break;
        }
        // add those two numbers
        double result = first + second;
        switch (resultTarget) {
            case Target::STACK:
                context->stack->doubles.push(result);
                break;
            case Target::LOCAL:
                context->storage->doubles.set(resultLocalIndex, result);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String DoubleAdd::debug() {
        String result = "dadd";
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

#pragma region DOUBLE_SUBTRACT
    /**
     * Initialize the double subtract instruction.
     */
    DoubleSubtract::DoubleSubtract()
        : Instruction(Instructions::DOUBLE_SUBTRACT)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoubleSubtract::parse(String data, List<String> args, uint line, Executable* executable) {
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
                    firstValue = stringToDouble(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToDouble(args[++i]);
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
    void DoubleSubtract::execute(Context* context) {
        // get the first value to be added
        double first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                first = context->storage->doubles.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        double second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                second = context->storage->doubles.get((uint) secondValue);
                break;
        }
        // add those two numbers
        double result = first - second;
        switch (resultTarget) {
            case Target::STACK:
                context->stack->doubles.push(result);
                break;
            case Target::LOCAL:
                context->storage->doubles.set(resultLocalIndex, result);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String DoubleSubtract::debug() {
        String result = "dsub";
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

#pragma region DOUBLE_MULTIPLY
    /**
     * Initialize the double subtract instruction.
     */
    DoubleMultiply::DoubleMultiply()
        : Instruction(Instructions::DOUBLE_MULTIPLY)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoubleMultiply::parse(String data, List<String> args, uint line, Executable* executable) {
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
                    firstValue = stringToDouble(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToDouble(args[++i]);
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
    void DoubleMultiply::execute(Context* context) {
        // get the first value to be added
        double first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                first = context->storage->doubles.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        double second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                second = context->storage->doubles.get((uint) secondValue);
                break;
        }
        // add those two numbers
        double result = first * second;
        switch (resultTarget) {
            case Target::STACK:
                context->stack->doubles.push(result);
                break;
            case Target::LOCAL:
                context->storage->doubles.set(resultLocalIndex, result);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String DoubleMultiply::debug() {
        String result = "dmul";
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

#pragma region DOUBLE_DIVIDE
    /**
     * Initialize the double divide instruction.
     */
    DoubleDivide::DoubleDivide()
        : Instruction(Instructions::DOUBLE_DIVIDE)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoubleDivide::parse(String data, List<String> args, uint line, Executable* executable) {
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
                    firstValue = stringToDouble(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToDouble(args[++i]);
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
    void DoubleDivide::execute(Context* context) {
        // get the first value to be added
        double first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                first = context->storage->doubles.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        double second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                second = context->storage->doubles.get((uint) secondValue);
                break;
        }
        // add those two numbers
        double result = first / second;
        switch (resultTarget) {
            case Target::STACK:
                context->stack->doubles.push(result);
                break;
            case Target::LOCAL:
                context->storage->doubles.set(resultLocalIndex, result);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String DoubleDivide::debug() {
        String result = "ddiv";
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

#pragma region DOUBLE_MODULO
    /**
     * Initialize the double modulo instruction.
     */
    DoubleModulo::DoubleModulo()
        : Instruction(Instructions::DOUBLE_MODULO)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoubleModulo::parse(String data, List<String> args, uint line, Executable* executable) {
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
                    firstValue = stringToDouble(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToDouble(args[++i]);
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
    void DoubleModulo::execute(Context* context) {
        // get the first value to be added
        double first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                first = context->storage->doubles.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        double second = secondValue;
            switch (secondTarget) {
            case Target::STACK:
                second = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                second = context->storage->doubles.get((uint) secondValue);
                break;
        }
        // add those two numbers
        double result = fmod(first, second);
        switch (resultTarget) {
            case Target::STACK:
                context->stack->doubles.push(result);
                break;
            case Target::LOCAL:
                context->storage->doubles.set(resultLocalIndex, result);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String DoubleModulo::debug() {
        String result = "dmod";
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

#pragma region DOUBLE_INCREMENT
    /**
     * Initialize the double increment instruction.
     */
    DoubleIncrement::DoubleIncrement()
        : Instruction(Instructions::DOUBLE_INCREMENT)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoubleIncrement::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void DoubleIncrement::execute(Context* context) {
        // get the value to be incremented
        double value = 0;
        switch (source) {
            case Target::STACK:
                value = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                value = context->storage->doubles.get(sourceIndex);
                break;
        }
        // increment the value
        value++;
        switch (result) {
        case Target::STACK:
                context->stack->doubles.push(value);
                break;
            case Target::LOCAL:
                context->storage->doubles.set(resultIndex, value);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String DoubleIncrement::debug() {
        String debug = "dinc";
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

#pragma region DOUBLE_DECREMENT
    /**
     * Initialize the double decrement instruction.
     */
    DoubleDecrement::DoubleDecrement()
        : Instruction(Instructions::DOUBLE_DECREMENT)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoubleDecrement::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void DoubleDecrement::execute(Context* context) {
        // get the value to be incremented
        double value = 0;
        switch (source) {
            case Target::STACK:
                value = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                value = context->storage->doubles.get(sourceIndex);
                break;
        }
        // increment the value
        value--;
        switch (result) {
            case Target::STACK:
                context->stack->doubles.push(value);
                break;
            case Target::LOCAL:
                context->storage->doubles.set(resultIndex, value);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String DoubleDecrement::debug() {
        String debug = "ddecr";
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

#pragma region DOUBLE_NEGATE
    /**
     * Initialize the double negate instruction.
     */
    DoubleNegate::DoubleNegate()
        : Instruction(Instructions::DOUBLE_NEGATE)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoubleNegate::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void DoubleNegate::execute(Context* context) {
        // get the value to be incremented
        double value = 0;
        switch (source) {
            case Target::STACK:
                value = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                value = context->storage->doubles.get(sourceIndex);
                break;
        }
        // negate the value
        value = -value;
        switch (result) {
            case Target::STACK:
                context->stack->doubles.push(value);
                break;
            case Target::LOCAL:
                context->storage->doubles.set(resultIndex, value);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String DoubleNegate::debug() {
        String debug = "dneg";
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

#pragma region DOUBLE_DEBUG
    /**
     * Initailize the double debug instruction.
     */
    DoubleDebug::DoubleDebug()
        : Instruction(Instructions::DOUBLE_DEBUG)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoubleDebug::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void DoubleDebug::execute(Context* context) {
        // get the value from the stack
        double value = context->stack->doubles.pull(keepStack);
        // double:pr the value and insert a new line if the flag is set
        print(value);
        if (newLine)
            println("");
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String DoubleDebug::debug() {
        String result = "ddebug";
        if (newLine)
            result += " -newline";
        if (keepStack)
            result += " -keepstack";
        return result;
    }
#pragma endregion

#pragma region DOUBLE_IF_EQUALS
    /**
         * Initialize the double equals check instruction.
         */
    DoubleEquals::DoubleEquals()
        : Instruction(Instructions::DOUBLE_IF_EQUAL)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoubleEquals::parse(String data, List<String> args, uint line, Executable* executable) {
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
                    firstValue = stringToDouble(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToDouble(args[++i]);
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
    void DoubleEquals::execute(Context* context) {
        // get the first value to be added
        double first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                first = context->storage->doubles.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        double second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                second = context->storage->doubles.get((uint) secondValue);
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
    String DoubleEquals::debug() {
        String result = "ifd==";
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

#pragma region DOUBLE_IF_NOT_EQUALS
    /**
     * Initialize the double not equals instruction.
     */
    DoubleNotEquals::DoubleNotEquals()
        : Instruction(Instructions::DOUBLE_IF_NOT_EQUAL)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoubleNotEquals::parse(String data, List<String> args, uint line, Executable* executable) {
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
                    firstValue = stringToDouble(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToDouble(args[++i]);
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
    void DoubleNotEquals::execute(Context* context) {
        // get the first value to be added
        double first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                first = context->storage->doubles.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        double second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                second = context->storage->doubles.get((uint) secondValue);
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
    String DoubleNotEquals::debug() {
        String result = "ifd!=";
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

#pragma region DOUBLE_IF_GREATER_THAN
    /**
     * Initialize the double greater than check instruction.
     */
    DoubleGreaterThan::DoubleGreaterThan()
        : Instruction(Instructions::DOUBLE_IF_GREATER_THAN)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoubleGreaterThan::parse(String data, List<String> args, uint line, Executable* executable) {
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
                    firstValue = stringToDouble(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToDouble(args[++i]);
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
    void DoubleGreaterThan::execute(Context* context) {
        // get the first value to be added
        double first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                first = context->storage->doubles.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        double second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                second = context->storage->doubles.get((uint) secondValue);
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
    String DoubleGreaterThan::debug() {
        String result = "ifd>";
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

#pragma region DOUBLE_IF_GREATER_THAN_OR_EQUAL
    /**
     * Initialize the double greater than check instruction.
     */
    DoubleGreaterThanOrEquals::DoubleGreaterThanOrEquals()
        : Instruction(Instructions::DOUBLE_IF_GREATER_THAN_OR_EQUAL)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoubleGreaterThanOrEquals::parse(String data, List<String> args, uint line, Executable* executable) {
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
                    firstValue = stringToDouble(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToDouble(args[++i]);
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
    void DoubleGreaterThanOrEquals::execute(Context* context) {
        // get the first value to be added
        double first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                first = context->storage->doubles.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        double second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                second = context->storage->doubles.get((uint) secondValue);
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
    String DoubleGreaterThanOrEquals::debug() {
        String result = "ifd>=";
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

#pragma region DOUBLE_IF_LESS_THAN
    /**
     * Initialize the double less than check instruction.
     */
    DoubleLessThan::DoubleLessThan()
        : Instruction(Instructions::DOUBLE_IF_LESS_THAN)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoubleLessThan::parse(String data, List<String> args, uint line, Executable* executable) {
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
                    firstValue = stringToDouble(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToDouble(args[++i]);
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
    void DoubleLessThan::execute(Context* context) {
        // get the first value to be added
        double first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                first = context->storage->doubles.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        double second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                second = context->storage->doubles.get((uint) secondValue);
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
    String DoubleLessThan::debug() {
        String result = "ifd<";
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

#pragma region DOUBLE_IF_LESS_THAN_OR_EQUAL
    /**
     * Initialize the double less than check instruction.
     */
    DoubleLessThanOrEqual::DoubleLessThanOrEqual()
        : Instruction(Instructions::DOUBLE_IF_LESS_THAN_OR_EQUAL)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoubleLessThanOrEqual::parse(String data, List<String> args, uint line, Executable* executable) {
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
                    firstValue = stringToDouble(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToDouble(args[++i]);
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
    void DoubleLessThanOrEqual::execute(Context* context) {
        // get the first value to be added
        double first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                first = context->storage->doubles.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        double second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->doubles.pull();
                break;
            case Target::LOCAL:
                second = context->storage->doubles.get((uint) secondValue);
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
    String DoubleLessThanOrEqual::debug() {
        String result = "ifd<=";
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

#pragma region DOUBLE_STACK_SIZE
    /**
     * Initailize the double stack size instruction.
     */
    DoubleStackSize::DoubleStackSize()
        : Instruction(Instructions::DOUBLE_STACK_SIZE)
    { }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void DoubleStackSize::execute(Context* context) {
        context->stack->doubles.push(context->stack->doubles.size());
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String DoubleStackSize::debug() {
        return "dstacksize";
    }
#pragma endregion

#pragma region DOUBLE_DUMP_STACK
    /**
     * Initialize the double stack dump instruction.
     */
    DoubleDumpStack::DoubleDumpStack()
        : Instruction(Instructions::DOUBLE_DUMP_STACK)
    { }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void DoubleDumpStack::execute(Context* context) {
        uint size = context->stack->doubles.size();;
        println("[log] double stack dump (" << size << ")");
        for (uint i = 0; i < size; i++) {
            println("- " << context->stack->doubles.at(i) << " [" << i << "]");
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String DoubleDumpStack::debug() {
        return "ddumpstack";
    }
#pragma endregion

#pragma region DOUBLE_CLEAR_STACK
    /**
     * Initialize the double stack clear instruction.
     */
    DoubleClearStack::DoubleClearStack()
        : Instruction(Instructions::DOUBLE_CLEAR_STACK)
    { }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void DoubleClearStack::execute(Context* context) {
        context->stack->doubles.clear();
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String DoubleClearStack::debug() {
        return "dclearstack";
    }
#pragma endregion

#pragma region DOUBLE_POP_STACK
    /**
     * Initialize the double pop instruction.
     */
    DoublePopStack::DoublePopStack()
        : Instruction(Instructions::DOUBLE_POP_STACK)
    { }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void DoublePopStack::execute(Context* context) {
        context->stack->doubles.pull();
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String DoublePopStack::debug() {
        return "dpop";
    }
#pragma endregion

#pragma region DOUBLE_DUPLICATE_STACK
    /**
     * Initialize the double duplicate instruction.
     */
    DoubleDuplicateStack::DoubleDuplicateStack()
        : Instruction(Instructions::DOUBLE_DUPLICATE_STACK)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void DoubleDuplicateStack::parse(String data, List<String> args, uint line, Executable* executable) {
        // parse the duplication count
        if (!args.empty())
            count = stringToInt(args[0]);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void DoubleDuplicateStack::execute(Context* context) {
        // get the value to be duplicated without being removed
        double value = context->stack->doubles.get();
        // push the value to the stack the given times
        for (uint i = 0; i < count; i++)
            context->stack->doubles.push(value);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String DoubleDuplicateStack::debug() {
        String result = "ddup";
        if (count > 1)
            result += " " + toString(count);
        return result;
    }
#pragma endregion
}