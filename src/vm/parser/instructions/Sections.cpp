#include "Sections.hpp"

namespace Void {
#pragma region SECTION
    /**
     * Initialize the section instruction.
     */
    Section::Section()
        : Instruction(Instructions::SECTION)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void Section::parse(String data, List<String> args, uint line, Executable* executable) {
        // parse the name of the section
        name = data.substr(1);
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String Section::debug() {
        return ":" + name;
    }
#pragma endregion

#pragma region GOTO
    /**
     * Initialize the goto instruction.
     */
    Goto::Goto() 
        : Instruction(Instructions::GOTO)
    { }

    /**
     * Parse raw bytecode instruction.
     * @param raw bytecode data
     * @parma args split array of the data
     * @param line bytecode line index
     * @param executable bytecode executor
     */
    void Goto::parse(String data, List<String> args, uint line, Executable* executable) {
        // parse the bytecode index from string
        index = executable->getSection(args[0]);
    }

    /**
     * Execute the instruction in the executable context.
     * @param context bytecode execution context
     */
    void Goto::execute(Context* context) {
        context->cursor = index;
    }

    /**
     * Get the string representation of the instruction.
     * @return instruction bytecode data
     */
    String Goto::debug() {
        return "goto " + toString(index);
    }
#pragma endregion
}