#include "Floats.hpp"

namespace Void {
#pragma region FLOAT_PUSH
    /**
     * Initialize the float push instruction.
     */
    FloatPush::FloatPush()
        : Instruction(Instructions::FLOAT_PUSH)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatPush::parse(String data, List<String> args, uint line, Executable* executable) {
        // parse the float value to be pushed to the stack
        value = stringToFloat(args[0]);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void FloatPush::execute(Context* context) {
        // pust the float value to the stack
        context->stack->floats.push(value);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String FloatPush::debug() {
        return "fpush " + toString(value);
    }
#pragma endregion

#pragma region FLOAT_LOAD
    /**
     * Initialize the float load instruction.
     */
    FloatLoad::FloatLoad()
        : Instruction(Instructions::FLOAT_LOAD)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatLoad::parse(String data, List<String> args, uint line, Executable* executable) {
        // try to parse the storage index from string
        index = executable->getLinker(args[0]);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void FloatLoad::execute(Context* context) {
        // load the value from the given storage slot
        // and push it to the stack
        context->stack->floats.push(context->storage->floats.get(index));
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String FloatLoad::debug() {
        return "fload " + toString(index);
    }
#pragma endregion

#pragma region FLOAT_STORE
    /**
     * Initialize the float store instruction.
     */
    FloatStore::FloatStore()
        : Instruction(Instructions::FLOAT_STORE)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatStore::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void FloatStore::execute(Context* context) {
        // load the value from the stack
        // and store it in the storage
        context->storage->floats.set(index, context->stack->floats.pull(keepStack));
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String FloatStore::debug() {
        String result = "fstore " + toString(index);
        if (keepStack)
            result += " -k";
        return result;
    }
#pragma endregion

#pragma region FLOAT_SET
    /**
     * Initialize the float set instruction.
     */
    FloatSet::FloatSet()
        : Instruction(Instructions::FLOAT_SET)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatSet::parse(String data, List<String> args, uint line, Executable* executable) {
        // try to parse the storage index from string
        index = executable->getLinker(args[0]);
        // parse the float value to be pushed to the stack
        value = stringToFloat(args[1]);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void FloatSet::execute(Context* context) {
        context->storage->floats.set(index, value);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String FloatSet::debug() {
        return "fset " + toString(index) + " " + toString(value);
    }
#pragma endregion

#pragma region FLOAT_ENSURE
    /**
     * Initialize the float ensure instruction.
     */
    FloatEnsure::FloatEnsure()
        : Instruction(Instructions::FLOAT_ENSURE)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatEnsure::parse(String data, List<String> args, uint line, Executable* executable) {
        // parse the float storage required size
        size = stringToInt(args[0]);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void FloatEnsure::execute(Context* context) {
        context->storage->ensure(StorageUnit::INT, size);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String FloatEnsure::debug() {
        return "fensure " + toString(size);
    }
#pragma endregion

#pragma region FLOAT_ADD
    /**
     * Initialize the float add instruction.
     */
    FloatAdd::FloatAdd()
        : Instruction(Instructions::FLOAT_ADD)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatAdd::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = (float) executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = (float) executable->getLinker(args[++i]);
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
                    firstValue = stringToFloat(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToFloat(args[++i]);
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
    void FloatAdd::execute(Context* context) {
        // get the first value to be added
        float first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                first = context->storage->floats.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        float second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                second = context->storage->floats.get((uint) secondValue);
                break;
        }
        // add those two numbers
        float result = first + second;
        switch (resultTarget) {
            case Target::STACK:
                context->stack->floats.push(result);
                break;
            case Target::LOCAL:
                context->storage->floats.set(resultLocalIndex, result);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String FloatAdd::debug() {
        String result = "fadd";
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

#pragma region FLOAT_SUBTRACT
    /**
     * Initialize the float subtract instruction.
     */
    FloatSubtract::FloatSubtract()
        : Instruction(Instructions::FLOAT_SUBTRACT)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatSubtract::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = (float) executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = (float) executable->getLinker(args[++i]);
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
                    firstValue = stringToFloat(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToFloat(args[++i]);
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
    void FloatSubtract::execute(Context* context) {
        // get the first value to be added
        float first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                first = context->storage->floats.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        float second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                second = context->storage->floats.get((uint) secondValue);
                break;
        }
        // add those two numbers
        float result = first - second;
        switch (resultTarget) {
            case Target::STACK:
                context->stack->floats.push(result);
                break;
            case Target::LOCAL:
                context->storage->floats.set(resultLocalIndex, result);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String FloatSubtract::debug() {
        String result = "fsub";
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

#pragma region FLOAT_MULTIPLY
    /**
     * Initialize the float subtract instruction.
     */
    FloatMultiply::FloatMultiply()
        : Instruction(Instructions::FLOAT_MULTIPLY)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatMultiply::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = (float) executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = (float) executable->getLinker(args[++i]);
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
                    firstValue = stringToFloat(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToFloat(args[++i]);
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
    void FloatMultiply::execute(Context* context) {
        // get the first value to be added
        float first = firstValue;
            switch (firstTarget) {
            case Target::STACK:
                first = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                first = context->storage->floats.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        float second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                second = context->storage->floats.get((uint) secondValue);
                break;
        }
        // add those two numbers
        float result = first * second;
        switch (resultTarget) {
            case Target::STACK:
                context->stack->floats.push(result);
                break;
            case Target::LOCAL:
                context->storage->floats.set(resultLocalIndex, result);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String FloatMultiply::debug() {
        String result = "fmul";
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

#pragma region FLOAT_DIVIDE
    /**
     * Initialize the float divide instruction.
     */
    FloatDivide::FloatDivide()
        : Instruction(Instructions::FLOAT_DIVIDE)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatDivide::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = (float) executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = (float) executable->getLinker(args[++i]);
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
                    firstValue = stringToFloat(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToFloat(args[++i]);
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
    void FloatDivide::execute(Context* context) {
        // get the first value to be added
        float first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                first = context->storage->floats.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        float second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                second = context->storage->floats.get((uint) secondValue);
                break;
        }
        // add those two numbers
        float result = first / second;
        switch (resultTarget) {
            case Target::STACK:
                context->stack->floats.push(result);
                break;
            case Target::LOCAL:
                context->storage->floats.set(resultLocalIndex, result);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String FloatDivide::debug() {
        String result = "fdiv";
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

#pragma region FLOAT_MODULO
    /**
     * Initialize the float modulo instruction.
     */
    FloatModulo::FloatModulo()
        : Instruction(Instructions::FLOAT_MODULO)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatModulo::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = (float) executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = (float) executable->getLinker(args[++i]);
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
                    firstValue = stringToFloat(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToFloat(args[++i]);
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
    void FloatModulo::execute(Context* context) {
        // get the first value to be added
        float first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                first = context->storage->floats.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        float second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                second = context->storage->floats.get((uint) secondValue);
                break;
        }
        // add those two numbers
        float result = fmodf(first, second);
        switch (resultTarget) {
            case Target::STACK:
                context->stack->floats.push(result);
                break;
            case Target::LOCAL:
                context->storage->floats.set(resultLocalIndex, result);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String FloatModulo::debug() {
        String result = "fmod";
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

#pragma region FLOAT_INCREMENT
    /**
     * Initialize the float increment instruction.
     */
    FloatIncrement::FloatIncrement()
        : Instruction(Instructions::FLOAT_INCREMENT)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatIncrement::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void FloatIncrement::execute(Context* context) {
        // get the value to be incremented
        float value = 0;
        switch (source) {
            case Target::STACK:
                value = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                value = context->storage->floats.get(sourceIndex);
                break;
        }
        // increment the value
        value++;
        switch (result) {
            case Target::STACK:
                context->stack->floats.push(value);
                break;
            case Target::LOCAL:
                context->storage->floats.set(resultIndex, value);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String FloatIncrement::debug() {
        String debug = "finc";
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

#pragma region FLOAT_DECREMENT
    /**
     * Initialize the float decrement instruction.
     */
    FloatDecrement::FloatDecrement()
        : Instruction(Instructions::FLOAT_DECREMENT)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatDecrement::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void FloatDecrement::execute(Context* context) {
        // get the value to be incremented
        float value = 0;
        switch (source) {
            case Target::STACK:
                value = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                value = context->storage->floats.get(sourceIndex);
                break;
        }
        // increment the value
        value--;
        switch (result) {
            case Target::STACK:
                context->stack->floats.push(value);
                break;
            case Target::LOCAL:
                context->storage->floats.set(resultIndex, value);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String FloatDecrement::debug() {
        String debug = "fdecr";
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

#pragma region FLOAT_NEGATE
    /**
     * Initialize the float negate instruction.
     */
    FloatNegate::FloatNegate()
        : Instruction(Instructions::FLOAT_NEGATE)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatNegate::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void FloatNegate::execute(Context* context) {
        // get the value to be incremented
        float value = 0;
        switch (source) {
            case Target::STACK:
                value = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                value = context->storage->floats.get(sourceIndex);
                break;
        }
        // negate the value
        value = -value;
        switch (result) {
            case Target::STACK:
                context->stack->floats.push(value);
                break;
            case Target::LOCAL:
                context->storage->floats.set(resultIndex, value);
                break;
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String FloatNegate::debug() {
        String debug = "fneg";
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

#pragma region FLOAT_DEBUG
    /**
     * Initailize the float debug instruction.
     */
    FloatDebug::FloatDebug()
        : Instruction(Instructions::FLOAT_DEBUG)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatDebug::parse(String data, List<String> args, uint line, Executable* executable) {
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
    void FloatDebug::execute(Context* context) {
        // get the value from the stack
        float value = context->stack->floats.pull(keepStack);
        // float:pr the value and insert a new line if the flag is set
        print(value);
        if (newLine)
            println("");
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String FloatDebug::debug() {
        String result = "fdebug";
        if (newLine)
            result += " -newline";
        if (keepStack)
            result += " -keepstack";
        return result;
    }
#pragma endregion

#pragma region FLOAT_IF_EQUALS
    /**
         * Initialize the float equals check instruction.
         */
    FloatEquals::FloatEquals()
        : Instruction(Instructions::FLOAT_IF_EQUAL)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatEquals::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = (float) executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = (float) executable->getLinker(args[++i]);
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
                    firstValue = stringToFloat(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToFloat(args[++i]);
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
    void FloatEquals::execute(Context* context) {
        // get the first value to be added
        float first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                first = context->storage->floats.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        float second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                second = context->storage->floats.get((uint) secondValue);
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
    String FloatEquals::debug() {
        String result = "iff==";
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

#pragma region FLOAT_IF_NOT_EQUALS
    /**
     * Initialize the float not equals instruction.
     */
    FloatNotEquals::FloatNotEquals()
        : Instruction(Instructions::FLOAT_IF_NOT_EQUAL)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatNotEquals::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = (float) executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = (float) executable->getLinker(args[++i]);
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
                    firstValue = stringToFloat(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToFloat(args[++i]);
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
    void FloatNotEquals::execute(Context* context) {
        // get the first value to be added
        float first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                first = context->storage->floats.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        float second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                second = context->storage->floats.get((uint) secondValue);
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
    String FloatNotEquals::debug() {
        String result = "iff!=";
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

#pragma region FLOAT_IF_GREATER_THAN
    /**
     * Initialize the float greater than check instruction.
     */
    FloatGreaterThan::FloatGreaterThan()
        : Instruction(Instructions::FLOAT_IF_GREATER_THAN)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatGreaterThan::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = (float) executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = (float) executable->getLinker(args[++i]);
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
                    firstValue = stringToFloat(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToFloat(args[++i]);
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
    void FloatGreaterThan::execute(Context* context) {
        // get the first value to be added
        float first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                first = context->storage->floats.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        float second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                second = context->storage->floats.get((uint) secondValue);
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
    String FloatGreaterThan::debug() {
        String result = "iff>";
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

#pragma region FLOAT_IF_GREATER_THAN_OR_EQUAL
    /**
     * Initialize the float greater than check instruction.
     */
    FloatGreaterThanOrEquals::FloatGreaterThanOrEquals()
        : Instruction(Instructions::FLOAT_IF_GREATER_THAN_OR_EQUAL)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatGreaterThanOrEquals::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = (float) executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = (float) executable->getLinker(args[++i]);
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
                    firstValue = stringToFloat(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToFloat(args[++i]);
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
    void FloatGreaterThanOrEquals::execute(Context* context) {
        // get the first value to be added
        float first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                first = context->storage->floats.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        float second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                second = context->storage->floats.get((uint) secondValue);
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
    String FloatGreaterThanOrEquals::debug() {
        String result = "iff>=";
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

#pragma region FLOAT_IF_LESS_THAN
    /**
     * Initialize the float less than check instruction.
     */
    FloatLessThan::FloatLessThan()
        : Instruction(Instructions::FLOAT_IF_LESS_THAN)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatLessThan::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = (float) executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = (float) executable->getLinker(args[++i]);
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
                    firstValue = stringToFloat(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToFloat(args[++i]);
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
    void FloatLessThan::execute(Context* context) {
        // get the first value to be added
        float first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                first = context->storage->floats.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        float second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                second = context->storage->floats.get((uint) secondValue);
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
    String FloatLessThan::debug() {
        String result = "iff<";
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

#pragma region FLOAT_IF_LESS_THAN_OR_EQUAL
    /**
     * Initialize the float less than check instruction.
     */
    FloatLessThanOrEqual::FloatLessThanOrEqual()
        : Instruction(Instructions::FLOAT_IF_LESS_THAN_OR_EQUAL)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatLessThanOrEqual::parse(String data, List<String> args, uint line, Executable* executable) {
        // loop through the instruction data
        bool firstVariable = true;
        for (uint i = 0; i < args.size(); i++) {
            // get the current argument
            String arg = args[i];
            // handle value from local variable
            if (arg == "-l" || arg == "-local") {
                if (firstVariable) {
                    firstTarget = Target::LOCAL;
                    firstValue = (float) executable->getLinker(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::LOCAL;
                    secondValue = (float) executable->getLinker(args[++i]);
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
                    firstValue = stringToFloat(args[++i]);
                    firstVariable = false;
                }
                else {
                    secondTarget = Target::CONSTANT;
                    secondValue = stringToFloat(args[++i]);
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
    void FloatLessThanOrEqual::execute(Context* context) {
        // get the first value to be added
        float first = firstValue;
        switch (firstTarget) {
            case Target::STACK:
                first = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                first = context->storage->floats.get((uint) firstValue);
                break;
        }
        // get the second value to be added
        float second = secondValue;
        switch (secondTarget) {
            case Target::STACK:
                second = context->stack->floats.pull();
                break;
            case Target::LOCAL:
                second = context->storage->floats.get((uint) secondValue);
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
    String FloatLessThanOrEqual::debug() {
        String result = "iff<=";
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

#pragma region FLOAT_STACK_SIZE
    /**
     * Initailize the float stack size instruction.
     */
    FloatStackSize::FloatStackSize()
        : Instruction(Instructions::FLOAT_STACK_SIZE)
    { }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void FloatStackSize::execute(Context* context) {
        context->stack->ints.push(context->stack->floats.size());
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String FloatStackSize::debug() {
        return "fstacksize";
    }
#pragma endregion

#pragma region FLOAT_DUMP_STACK
    /**
     * Initialize the float stack dump instruction.
     */
    FloatDumpStack::FloatDumpStack()
        : Instruction(Instructions::FLOAT_DUMP_STACK)
    { }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void FloatDumpStack::execute(Context* context) {
        uint size = context->stack->floats.size();;
        println("[log] float stack dump (" << size << ")");
        for (uint i = 0; i < size; i++) {
            println("- " << context->stack->floats.at(i) << " [" << i << "]");
        }
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String FloatDumpStack::debug() {
        return "fdumpstack";
    }
#pragma endregion

#pragma region FLOAT_CLEAR_STACK
    /**
     * Initialize the float stack clear instruction.
     */
    FloatClearStack::FloatClearStack()
        : Instruction(Instructions::FLOAT_CLEAR_STACK)
    { }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void FloatClearStack::execute(Context* context) {
        context->stack->floats.clear();
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String FloatClearStack::debug() {
        return "fclearstack";
    }
#pragma endregion

#pragma region FLOAT_POP_STACK
    /**
     * Initialize the float pop instruction.
     */
    FloatPopStack::FloatPopStack()
        : Instruction(Instructions::FLOAT_POP_STACK)
    { }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void FloatPopStack::execute(Context* context) {
        context->stack->floats.pull();
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String FloatPopStack::debug() {
        return "fpop";
    }
#pragma endregion

#pragma region FLOAT_DUPLICATE_STACK
    /**
     * Initialize the float duplicate instruction.
     */
    FloatDuplicateStack::FloatDuplicateStack()
        : Instruction(Instructions::FLOAT_DUPLICATE_STACK)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void FloatDuplicateStack::parse(String data, List<String> args, uint line, Executable* executable) {
        // parse the duplication count
        if (!args.empty())
            count = stringToInt(args[0]);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void FloatDuplicateStack::execute(Context* context) {
        // get the value to be duplicated without being removed
        float value = context->stack->floats.get();
        // push the value to the stack the given times
        for (uint i = 0; i < count; i++)
            context->stack->floats.push(value);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String FloatDuplicateStack::debug() {
        String result = "fdup";
        if (count > 1)
            result += " " + toString(count);
        return result;
    }
#pragma endregion
}
