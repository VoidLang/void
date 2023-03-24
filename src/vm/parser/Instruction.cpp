#include "Instruction.hpp"
#include "../../util/Strings.hpp"
#include "instructions/Integers.hpp"
#include "instructions/Longs.hpp"
#include "instructions/Sections.hpp"

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
        if (identifier[0] == ':')
            return new Section();
        else if (identifier == "goto")
            return new Goto();
        else if (identifier == "#link")
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
        else if (identifier == "iadd")
            return new IntegerAdd();
        else if (identifier == "isub")
            return new IntegerSubtract();
        else if (identifier == "imul")
            return new IntegerMultiply();
        else if (identifier == "idiv")
            return new IntegerDivide();
        else if (identifier == "imod")
            return new IntegerModulo();
        else if (identifier == "iinc")
            return new IntegerIncrement();
        else if (identifier == "idecr")
            return new IntegerDecrement();
        else if (identifier == "ineg")
            return new IntegerNegate();
        else if (identifier == "idebug")
            return new IntegerDebug();
        else if (identifier == "ifieq" || identifier == "ifi==")
            return new IntegerEquals();
        else if (identifier == "ifineq" || identifier == "ifi!=")
            return new IntegerNotEquals();
        else if (identifier == "ifig" || identifier == "ifi>")
            return new IntegerGreaterThan();
        else if (identifier == "ifige" || identifier == "ifi>=")
            return new IntegerGreaterThanOrEquals();
        else if (identifier == "ifil" || identifier == "ifi<")
            return new IntegerLessThan();
        else if (identifier == "ifile" || identifier == "ifi<=")
            return new IntegerLessThanOrEqual();
        else if (identifier == "istacksize")
            return new IntegerStackSize();
        else if (identifier == "idumpstack")
            return new IntegerDumpStack();
        else if (identifier == "iclearstack")
            return new IntegerClearStack();
        else if (identifier == "ipop")
            return new IntegerPopStack();
        else if (identifier == "idup")
            return new IntegerDuplicateStack();
#pragma endregion

#pragma region Longs
        else if (identifier == "lpush")
            return new LongPush();
        else if (identifier == "lload")
            return new LongLoad();
        else if (identifier == "lstore")
            return new LongStore();
        else if (identifier == "lset")
            return new LongSet();
        else if (identifier == "lensure")
            return new LongEnsure();
        else if (identifier == "ladd")
            return new LongAdd();
        else if (identifier == "lsub")
            return new LongSubtract();
        else if (identifier == "lmul")
            return new LongMultiply();
        else if (identifier == "ldiv")
            return new LongDivide();
        else if (identifier == "lmod")
            return new LongModulo();
        else if (identifier == "linc")
            return new LongIncrement();
        else if (identifier == "ldecr")
            return new LongDecrement();
        else if (identifier == "lneg")
            return new LongNegate();
        else if (identifier == "ldebug")
            return new LongDebug();
        else if (identifier == "ifleq" || identifier == "ifl==")
            return new LongEquals();
        else if (identifier == "iflneq" || identifier == "ifl!=")
            return new LongNotEquals();
        else if (identifier == "iflg" || identifier == "ifl>")
            return new LongGreaterThan();
        else if (identifier == "iflge" || identifier == "ifl>=")
            return new LongGreaterThanOrEquals();
        else if (identifier == "ifll" || identifier == "ifl<")
            return new LongLessThan();
        else if (identifier == "iflle" || identifier == "ifl<=")
            return new LongLessThanOrEqual();
        else if (identifier == "lstacksize")
            return new LongStackSize();
        else if (identifier == "ldumpstack")
            return new LongDumpStack();
        else if (identifier == "lclearstack")
            return new LongClearStack();
        else if (identifier == "lpop")
            return new LongPopStack();
        else if (identifier == "ldup")
            return new LongDuplicateStack();
#pragma endregion

        else if (identifier == "print")
            return new Print();
        else if (identifier == "println")
            return new PrintLine();

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

    /**
     * Initialize the print instruction.
     */
    Print::Print()
        : Instruction(Instructions::PRINT)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void Print::parse(String data, List<String> args, uint line, Executable* executable) {
        text = data.substr(7, data.length() - 7 - 1);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void Print::execute(Context* context) {
        print(text);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String Print::debug() {
        return "print \"" + text + "\"";
    }

    /**
     * Initialize the print instruction.
     */
    PrintLine::PrintLine()
        : Instruction(Instructions::PRINT_LINE)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @aram executable bytecode executor
     */
    void PrintLine::parse(String data, List<String> args, uint line, Executable* executable) {
        text = data.substr(9, data.length() - 9 - 1);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void PrintLine::execute(Context* context) {
        println(text);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String PrintLine::debug() {
        return "println \"" + text + "\"";
    }
}
