#pragma once

#include "../Instruction.hpp"

#ifdef VOID_INSTRUCTION
namespace Void {
#pragma region SECTION
    /**
     * Represents a jump section declaration.
     */
    class Section : public Instruction {
    private:
        /**
         * The name of the section.
         */
        String name;

    public:
        /**
         * Initialize the section instruction. 
         */
        Section();

        /**
         * Parse raw bytecode instruction.
         * @param raw bytecode data
         * @parma args split array of the data
         * @param line bytecode line index
         * @param executable bytecode executor
         */
        void parse(String data, List<String> args, uint line, Executable* executable) override;

        /**
         * Get the string representation of the instruction.
         * @return instruction bytecode data
         */
        String debug() override;
    };
#pragma endregion

#pragma region GOTO
    /**
     * Represents an instruction that jumps to a given section.
     */
    class Goto : public Instruction {
    private:
        /**
         * The bytecode instruction index to jump to.
         */
        ulong index = 0;

    public:
        /**
         * Initialize the goto instruction.
         */
        Goto();

        /**
         * Parse raw bytecode instruction.
         * @param raw bytecode data
         * @parma args split array of the data
         * @param line bytecode line index
         * @param executable bytecode executor
         */
        void parse(String data, List<String> args, uint line, Executable* executable) override;

        /**
         * Execute the instruction in the executable context.
         * @param context bytecode execution context
         */
        void execute(Context* context) override;

        /**
         * Get the string representation of the instruction.
         * @return instruction bytecode data
         */
        String debug() override;
    };
#pragma endregion

#pragma region RETURN
    /**
     * Represents an instruction that terminates the method execution context.
     */
    class Return : public Instruction {
    public:
        /**
         * Initialize the return instruction.
         */
        Return();

        /**
         * Execute the instruction in the executable context.
         * @param context bytecode execution context
         */
        void execute(Context* context) override;

        /**
         * Get the string representation of the instruction.
         * @return instruction bytecode data
         */
        String debug() override;
    };
#pragma endregion
}
#endif