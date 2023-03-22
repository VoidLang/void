#include "Instruction.hpp"
#include "../../util/Strings.hpp"
#include "instructions/Integers.hpp"

namespace Void {
    /**
     * Create an equalence check for a string and instruction.
     */
    bool operator==(String string, Instructions instruction) {
        // check if the name matches the instruction
        return string == ELEMENT_INSTRUCTIONS_MAPPED[static_cast<int>(instruction)]
            || string == ELEMENT_INSTRUCTIONS_UNMAPPED[static_cast<int>(instruction)];
    }

    /**
     * Initialize instruction.
     */
    Instruction::Instruction(Instructions kind) : kind(kind) 
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void Instruction::parse(String data, List<String> args, uint line, Executable* executable)
    { }

    /**
     * Initialize the references in the const pool after the whole program has been parsed.
     * @param vm running virtual machine
     * @param executable bytecode executor
     */
    void Instruction::initialize(VirtualMachine* vm, Executable* executable)
    { }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void Instruction::execute(Context* context)
    { }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String Instruction::debug() {
        return "<not implemented>";
    }

    /**
     * Create an instruction from raw bytecode input.
     * @param data raw bytecode instruction
     * @param line current bytecode line index
     * @param executable bytecode executor
     */
    Instruction* Instruction::of(String data, uint line, Executable* executable) {
        // split the raw bytecode instruction
        List<String> args = Strings::split(data, ' ');
        String identifier = args[0];

        // find the instruction wrapper from instruction name
        Instruction* instruction = createWrapper(identifier);

        // remove the identifier from the instruction arguments
        args.erase(args.begin());
        // parse the instruction data
        instruction->parse(data, args, line, executable);

        return instruction;
    }

    /**
     * Instantiate a bytecode instruction wrapper by its identifier.
     * @param identifier instruction identifier
     * @return new instruction wrapper
     */
    Instruction* Instruction::createWrapper(String identifier) {
        if (identifier == "#link")
            return new Linker();

#pragma region Integers
        else if (identifier == "ipush")
            return new IntegerPush();
        else if (identifier == "iload")
            return new IntegerLoad();
        else if (identifier == "istore")
            return new IntegerStore();
        else if (identifier == "iset")
            return new IntegerSet();
        else if (identifier == "iensure")
            return new IntegerEnsure();
        else if (identifier == "idebug")
            return new IntegerDebug();
#pragma endregion

        else
            return new EmptyInstruction();
    }

    /**
     * Initialize the execution context.
     */
    Context::Context(Stack* stack, Storage* storage, ulong length, Executable* executable)
        : stack(stack), storage(storage), length(length), 
          executable(executable), cursor(0), result(nullptr)
    { }

    /**
     * Initialize the instruction.
     */
    EmptyInstruction::EmptyInstruction()
        : Instruction(Instructions::NONE)
    { }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String EmptyInstruction::debug() {
        return "<unrecognized instruction>";
    }

    /**
     * Initialize the linker instruction.
     */
    Linker::Linker()
        : Instruction(Instructions::LINKER)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void Linker::parse(String data, List<String> args, uint line, Executable* executable) {
        // parse the variable name of the linker
        variable = args[0];
        // parse the line number of the linker
        index = stringToInt(args[1]);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String Linker::debug() {
        return "#link " + variable + " " + toString(index);
    }
}
