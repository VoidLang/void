#pragma once

#include "../../Common.hpp"
#include "../element/Executable.hpp"

#ifndef VOID_INSTRUCTION
#define VOID_INSTRUCTION
namespace Void {
    class Stack;
    class Storage;
    class Executable;
    class VirtualMachine;

    /**
     * Represents a holder of the registered bytecode instructions.
     */
    enum class Instructions {
#pragma region Classes

        /**
         * Start the declaration of a class.
         */
        CLASS_DEFINE,

        /**
         * Set the access modifiers of the class.
         */
        CLASS_MODIFIERS,

        /**
         * Set the superclass of the class.
         */
        CLASS_EXTENDS,

        /**
         * Set the interfaces of the class.
         */
        CLASS_IMPLEMENTS,

        /**
         * Begin the content declaration of the class.
         */
        CLASS_BEGIN,

        /**
         * End the content declaration of the class.
         */
        CLASS_END,

#pragma endregion

#pragma region Methods

        /**
         * Start the declaration of a method.
         */
        METHOD_DEFINE,

        /**
         * Set the access modifiers of the method.
         */
        METHOD_MODIFIERS,

        /**
         * Set the return type of the method.
         */
        METHOD_RETURN_TYPE,

        /**
         * Set the parameters of the method.
         */
        METHOD_PARAMETERS,

        /**
         * Begin the content declaration of the method.
         */
        METHOD_BEGIN,

        /**
         * End the content declaration of the method.
         */
        METHOD_END,

#pragma endregion

#pragma region Fields

        /**
         * Start the declaration of a field.
         */
        FIELD_DEFINE,

        /**
         * Set the access modifiers of the field.
         */
        FIELD_MODIFIERS,

        /**
         * Set the type of the field.
         */
        FIELD_TYPE,

        /**
         * Begin the content declaration of the field.
         */
        FIELD_BEGIN,

        /**
         * End the content declaration of the field.
         */
        FIELD_END,

        /**
         * Get the value of a field and put in on the stack.
         */
        FIELD_GET,

        /**
         * Get the value of a static field and put in on the stack.
         */
        FIELD_STATIC_GET,

        /**
         * Set the value of a field from the stack.
         */
        FIELD_SET,

        /**
         * Set the value of a static field from the stack.
         */
        FIELD_STATIC_SET,

#pragma endregion

        /**
         * Create a jump section.
         */
        SECTION,

        /**
         * Jump to the given section or line index.
         */
        GOTO,

        /**
         * Link a variable name to a storage unit.
         */
        LINKER,

#pragma region Integers

        /**
         * Push an integer to the stack.
         */
        INTEGER_PUSH,

        /**
         * Load an integer from the storage to the stack.
         */
        INTEGER_LOAD,

        /**
         * Store an integer from the stack to the storage.
         */
        INTEGER_STORE,

        /**
         * Store an integer in the storage with keeping the value in the stack.
         */
        INTEGER_STORE_KEEP_STACK,

        /**
         * Load an integer value from an array.
         */
        INTEGER_ARRAY_LOAD,

        /**
         * Store an integer value in an array.
         */
        INTEGER_ARRAY_STORE,

        /**
         * Add two integers from the stack.
         */
        INTEGER_ADD,

        /**
         * Substract two integers from the stack.
         */
        INTEGER_SUBTRACT,

        /**
         * Multiply two integers from the stack.
         */
        INTEGER_MULTIPLY,

        /**
         * Divide two integers from the stack.
         */
        INTEGER_DIVIDE,

        /**
         * Get the module of two integers from the stack.
         */
        INTEGER_MODULO,

        /**
         * Increment the integer value on the stack by one.
         */
        INTEGER_INCREMENT,

        /**
         * Decrement the integer value on the stack by one.
         */
        INTEGER_DECREMENT,

        /**
         * Negate the integer on the stack.
         */
        INTEGER_NEGATE,

        /**
         * Return an integer value from the stack.
         */
        INTEGER_RETURN,

        /**
         * Remove the last integer from the stack.
         */
        INTEGER_POP_STACK,

        /**
         * Duplicate the integer on the stack.
         */
        INTEGER_DUPLICATE_STACK,

        /**
         * Duplicate the integer on the stack N times.
         */
        INTEGER_DUPLICATE_STACK_TIMES,

        /**
         * Print the integer on the stack.
         */
        INTEGER_DEBUG,

        /**
         * Get the count of integers on the stack and push the result back.
         */
        INTEGER_STACK_SIZE,

        /**
         * Clear the content of the integer stack.
         */
        INTEGER_CLEAR_STACK,

        /**
         * Pre-allocate the given amount of integer storage slots.
         */
        INTEGER_ALLOCATE,

        /**
         * Check if two integers are equal.
         */
        INTEGER_IF_EQUAL,

        /**
         * Check if two integers aren't equal.
         */
        INTEGER_IF_NOT_EQUAL,

        /**
         * Check if an integer is greater than another.
         */
        INTEGER_IF_GREATER_THAN,

        /**
         * Check if an integer is either greater than or is equal to another.
         */
        INTEGER_IF_GREATER_THAN_OR_EQUAL,

        /**
         * Check if an integer is less than another.
         */
        INTEGER_IF_LESS_THAN,

        /**
         * Check if an integer is either less than or is equal to another.
         */
        INTEGER_IF_LESS_THAN_OR_EQUAL,

#pragma endregion

#pragma region Floats

        /**
         * Push a float to the stack.
         */
        FLOAT_PUSH,

        /**
         * Load a float from the storage to the stack.
         */
        FLOAT_LOAD,

        /**
          * Store a float from the stack to the storage.
          */
        FLOAT_STORE,

        /**
         * Store a float in the storage with keeping the value in the stack.
         */
        FLOAT_STORE_KEEP_STACK,

        /**
         * Load a float value from an array.
         */
        FLOAT_ARRAY_LOAD,

        /**
         * Store a float value in an array.
         */
        FLOAT_ARRAY_STORE,

        /**
         * Add two floats from the stack.
         */
        FLOAT_ADD,

        /**
         * Substract two floats from the stack.
         */
        FLOAT_SUBTRACT,

        /**
         * Multiply two floats from the stack.
         */
        FLOAT_MULTIPLY,

        /**
         * Divide two floats from the stack.
         */
        FLOAT_DIVIDE,

        /**
         * Get the module of two floats from the stack.
         */
        FLOAT_MODULO,

        /**
         * Increment the float value on the stack by one.
         */
        FLOAT_INCREMENT,

        /**
         * Decrement the float value on the stack by one.
         */
        FLOAT_DECREMENT,

        /**
         * Negate the float on the stack.
         */
        FLOAT_NEGATE,

        /**
         * Return a float value from the stack.
         */
        FLOAT_RETURN,

        /**
         * Remove the last float from the stack.
         */
        FLOAT_POP_STACK,

        /**
         * Duplicate the float on the stack.
         */
        FLOAT_DUPLICATE_STACK,

        /**
         * Duplicate the float on the stack N times.
         */
        FLOAT_DUPLICATE_STACK_TIMES,

        /**
         * Prfloat the float on the stack.
         */
        FLOAT_DEBUG,

        /**
         * Get the count of floats on the stack and push the result back.
         */
        FLOAT_STACK_SIZE,

        /**
         * Clear the content of the float stack.
         */
        FLOAT_CLEAR_STACK,

        /**
         * Pre-allocate the given amount of float storage slots.
         */
        FLOAT_ALLOCATE,

        /**
         * Check if two floats are equal.
         */
        FLOAT_IF_EQUAL,

        /**
         * Check if two floats aren't equal.
         */
        FLOAT_IF_NOT_EQUAL,

        /**
         * Check if a float is greater than another.
         */
        FLOAT_IF_GREATER_THAN,

        /**
         * Check if a float is either greater than or is equal to another.
         */
        FLOAT_IF_GREATER_THAN_OR_EQUAL,

        /**
         * Check if a float is less than another.
         */
        FLOAT_IF_LESS_THAN,

        /**
         * Check if a float is either less than or is equal to another.
         */
        FLOAT_IF_LESS_THAN_OR_EQUAL,

#pragma endregion

#pragma region Doubles

        /**
         * Push a double to the stack.
         */
        DOUBLE_PUSH,

        /**
         * Load a double from the storage to the stack.
         */
        DOUBLE_LOAD,

        /**
         * Store a double from the stack to the storage.
         */
        DOUBLE_STORE,

        /**
         * Store a double in the storage with keeping the value in the stack.
         */
        DOUBLE_STORE_KEEP_STACK,

        /**
         * Load a double value from an array.
         */
        DOUBLE_ARRAY_LOAD,

        /**
         * Store a double value in an array.
         */
        DOUBLE_ARRAY_STORE,

        /**
         * Add two doubles from the stack.
         */
        DOUBLE_ADD,

        /**
         * Substract two doubles from the stack.
         */
        DOUBLE_SUBTRACT,

        /**
         * Multiply two doubles from the stack.
         */
        DOUBLE_MULTIPLY,

        /**
         * Divide two doubles from the stack.
         */
        DOUBLE_DIVIDE,

        /**
         * Get the module of two doubles from the stack.
         */
        DOUBLE_MODULO,

        /**
         * Increment the double value on the stack by one.
         */
        DOUBLE_INCREMENT,

        /**
         * Decrement the double value on the stack by one.
         */
        DOUBLE_DECREMENT,

        /**
         * Negate the double on the stack.
         */
        DOUBLE_NEGATE,

        /**
         * Return a double value from the stack.
         */
        DOUBLE_RETURN,

        /**
         * Remove the last double from the stack.
         */
        DOUBLE_POP_STACK,

        /**
         * Duplicate the double on the stack.
         */
        DOUBLE_DUPLICATE_STACK,

        /**
         * Duplicate the double on the stack N times.
         */
        DOUBLE_DUPLICATE_STACK_TIMES,

        /**
         * Prdouble the double on the stack.
         */
        DOUBLE_DEBUG,

        /**
         * Get the count of doubles on the stack and push the result back.
         */
        DOUBLE_STACK_SIZE,

        /**
         * Clear the content of the double stack.
         */
        DOUBLE_CLEAR_STACK,

        /**
         * Pre-allocate the given amount of double storage slots.
         */
        DOUBLE_ALLOCATE,

        /**
         * Check if two doubles are equal.
         */
        DOUBLE_IF_EQUAL,

        /**
         * Check if two doubles aren't equal.
         */
        DOUBLE_IF_NOT_EQUAL,

        /**
         * Check if a double is greater than another.
         */
        DOUBLE_IF_GREATER_THAN,

        /**
         * Check if a double is either greater than or is equal to another.
         */
        DOUBLE_IF_GREATER_THAN_OR_EQUAL,

        /**
         * Check if a double is less than another.
         */
        DOUBLE_IF_LESS_THAN,

        /**
         * Check if a double is either less than or is equal to another.
         */
        DOUBLE_IF_LESS_THAN_OR_EQUAL,

#pragma endregion

#pragma region Longs

        /**
         * Push a long to the stack.
         */
        LONG_PUSH,

        /**
         * Load a long from the storage to the stack.
         */
        LONG_LOAD,

        /**
         * Store a long from the stack to the storage.
         */
        LONG_STORE,

        /**
         * Store a long in the storage with keeping the value in the stack.
         */
        LONG_STORE_KEEP_STACK,

        /**
         * Load a long value from an array.
         */
        LONG_ARRAY_LOAD,

        /**
         * Store a long value in an array.
         */
        LONG_ARRAY_STORE,

        /**
         * Add two longs from the stack.
         */
        LONG_ADD,

        /**
         * Substract two longs from the stack.
         */
        LONG_SUBTRACT,

        /**
         * Multiply two longs from the stack.
         */
        LONG_MULTIPLY,

        /**
         * Divide two longs from the stack.
         */
        LONG_DIVIDE,

        /**
         * Get the module of two longs from the stack.
         */
        LONG_MODULO,

        /**
         * Increment the long value on the stack by one.
         */
        LONG_INCREMENT,

        /**
         * Decrement the long value on the stack by one.
         */
        LONG_DECREMENT,

        /**
         * Negate the long on the stack.
         */
        LONG_NEGATE,

        /**
         * Return a long value from the stack.
         */
        LONG_RETURN,

        /**
         * Remove the last long from the stack.
         */
        LONG_POP_STACK,

        /**
         * Duplicate the long on the stack.
         */
        LONG_DUPLICATE_STACK,

        /**
         * Duplicate the long on the stack N times.
         */
        LONG_DUPLICATE_STACK_TIMES,

        /**
         * PrLLONG the long on the stack.
         */
        LONG_DEBUG,

        /**
         * Get the count of longs on the stack and push the result back.
         */
        LONG_STACK_SIZE,

        /**
         * Clear the content of the long stack.
         */
        LONG_CLEAR_STACK,

        /**
         * Pre-allocate the given amount of long storage slots.
         */
        LONG_ALLOCATE,

        /**
         * Check if two longs are equal.
         */
        LONG_IF_EQUAL,

        /**
         * Check if two longs aren't equal.
         */
        LONG_IF_NOT_EQUAL,

        /**
         * Check if a long is greater than another.
         */
        LONG_IF_GREATER_THAN,

        /**
         * Check if a long is either greater than or is equal to another.
         */
        LONG_IF_GREATER_THAN_OR_EQUAL,

        /**
         * Check if a long is less than another.
         */
        LONG_IF_LESS_THAN,

        /**
         * Check if a long is either less than or is equal to another.
         */
        LONG_IF_LESS_THAN_OR_EQUAL,

#pragma endregion

#pragma region Instances

        /**
         * Create a new instance of the given class type.
         */
        NEW,

        /**
         * Push a null value to the instance stack.
         */
        NULLPTR,

        /**
         * Get the debug message of the instance on the stack.
         */
        INSTANCE_DEBUG,

        /**
         * Delete an instance from the memory.
         */
        INSTANCE_DELETE,

        ARRAY_DELETE,

        /**
         * Load an instance from the storage to the stack.
         */
        INSTANCE_LOAD,

        /**
         * Store an instance from the stack to the storage.
         */
        INSTANCE_STORE,

        /**
         * Get the address of the instance on the stack.
         */
        INSTANCE_GET_ADDRESS,

        /**
         * Set the value of the instance at the given address. Delete the previous instance on the address.
         */
        INSTANCE_SET_ADDRESS,

        /**
         * Set the value of the instance at the given address.
         */
        INSTANCE_SWAP_ADDRESS,

#pragma endregion

        INVOKE_STATIC,

        INPUT,

        NONE
    };

    /**
     * The registry of the mapped instruction names.
     */
    static const char* ELEMENT_INSTRUCTIONS_MAPPED[109] = {
        "cdef",
        "cmod",
        "cext",
        "cimpl",
        "cbegin",
        "cend",

        "mdef",
        "mmod",
        "mreturn",
        "mparam",
        "mbegin",
        "mend",

        "fdef",
        "fmod",
        "ftype",
        "fbegin",
        "fend",
        "getfield",
        "getstatic",
        "setfield",
        "setstatic",

        "section",
        "goto",
        "linker",

        "ipush",
        "iload",
        "istore",
        "istorew",
        "iaload",
        "iastore",
        "iadd",
        "isub",
        "imul",
        "idiv",
        "imod",
        "iinc",
        "idecr",
        "ineg",
        "ireturn",
        "ipop",
        "idup",
        "idup_x",
        "idebug",
        "istacksize",
        "iclearstack",
        "ialloc",
        "ifieq",
        "ifineq",
        "ifig",
        "ifige",
        "ifil",
        "ifile",

        "fpush",
        "fload",
        "fstore",
        "fstorew",
        "faload",
        "fastore",
        "fadd",
        "fsub",
        "fmul",
        "fdiv",
        "fmod",
        "finc",
        "fdecr",
        "fneg",
        "freturn",
        "fpop",
        "fdup",
        "fdup_x",
        "fdebug",
        "fstacksize",
        "fclearstack",
        "falloc",
        "iffeq",
        "iffneq",
        "iffg",
        "iffge",
        "iffl",
        "iffle",

        "dpush",
        "dload",
        "dstore",
        "dstorew",
        "daload",
        "dastore",
        "dadd",
        "dsub",
        "dmul",
        "ddiv",
        "dmod",
        "dinc",
        "ddecr",
        "dneg",
        "dreturn",
        "dpop",
        "ddup",
        "ddup_x",
        "ddebug",
        "dstacksize",
        "dclearstack",
        "dalloc",
        "ifdeq",
        "ifdneq",
        "ifdg",
        "ifdge",
        "ifdl",
        "ifdle",

        "invokestatic"
    };

    /**
     * The registry of the unmapped raw instruction values.
     */
    static const char* ELEMENT_INSTRUCTIONS_UNMAPPED[109] = {
        "cdef",
        "cmod",
        "cext",
        "cimpl",
        "cbegin",
        "cend",

        "mdef",
        "mmod",
        "mreturn",
        "mparam",
        "mbegin",
        "mend",

        "fdef",
        "fmod",
        "ftype",
        "fbegin",
        "fend",
        "getfield",
        "getstatic",
        "setfield",
        "setstatic",

        "section",
        "goto",
        "linker",

        "ipush",
        "iload",
        "istore",
        "istorew",
        "iaload",
        "iastore",
        "iadd",
        "isub",
        "imul",
        "idiv",
        "imod",
        "iinc",
        "idecr",
        "ineg",
        "ireturn",
        "ipop",
        "idup",
        "idup_x",
        "idebug",
        "istacksize",
        "iclearstack",
        "ialloc",
        "ifieq",
        "ifineq",
        "ifig",
        "ifige",
        "ifil",
        "ifile",

        "fpush",
        "fload",
        "fstore",
        "fstorew",
        "faload",
        "fastore",
        "fadd",
        "fsub",
        "fmul",
        "fdiv",
        "fmod",
        "finc",
        "fdecr",
        "fneg",
        "freturn",
        "fpop",
        "fdup",
        "fdup_x",
        "fdebug",
        "fstacksize",
        "fclearstack",
        "falloc",
        "ffieq",
        "ffineq",
        "ffig",
        "ffige",
        "ffil",
        "ffile",

        "invokestatic"
    };

    /**
     * Create an equalence check for a string and instruction.
     */
    bool operator==(String string, Instructions instruction);

    /**
     * Represents a bytecode executing context. A context is created for every invocation of methods and fields.
     */
    class Context {
    public:
        /**
         * The value stack of the caller executable context.
         */
        Stack* stack;

        /**
         * The variable storage of the caller executable context.
         */
        Storage* storage;

        /**
         * The current index of the executing bytecode.
         */
        uint cursor;

        /**
         * The total length of the executing bytecode.
         */
        uint length;

        /**
         * The result object of the bytecode execution.
         */
        Object result;

        /**
         * The executor of the bytecode.
         */
        Executable* executable;

        /**
         * Initialize the execution context.
         */
        Context(Stack* stack, Storage* storage, uint length, Executable* executable);
    };

    /**
     * Represents an executable bytecode instruction.
     */
    class Instruction {
    public:
        /**
         * The type of the instruction.
         */
        Instructions kind;

        /**
         * Initialize the instruction.
         */
        Instruction(Instructions kind);

        /**
         * Parse raw bytecode instruction.
         * @param raw bytecode data
         * @parma args split array of the data
         * @param line bytecode line index
         * @aram executable bytecode executor
         */
        virtual void parse(String data, List<String> args, uint line, Executable* executable);

        /**
         * Initialize the references in the const pool after the whole program has been parsed.
         * @param vm running virtual machine
         * @param executable bytecode executor
         */
        virtual void initialize(VirtualMachine* vm, Executable* executable);

        /**
         * Execute the instruction in the executable context.
         * @param context bytecode execution context
         */
        virtual void execute(Context* context);

        /**
         * Get the string representation of the instruction.
         * @return instruction bytecode data
         */
        virtual String debug();

        /**
         * Create an instruction from raw bytecode input.
         * @param data raw bytecode instruction
         * @param line current bytecode line index
         * @param executable bytecode executor
         */
        static Instruction* of(String data, uint line, Executable* executable);
    };

    /**
     * Represents a dummy instruction that does nothing
     */
    class EmptyInstruction : public Instruction {
    public:
        /**
         * Initialize the instruction.
         */
        EmptyInstruction();

        /**
         * Get the string representation of the instruction.
         * @return instruction bytecode data
         */
        String debug() override;
    };
}
#endif