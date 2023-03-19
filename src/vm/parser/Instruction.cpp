#include "Instruction.hpp"

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
}
