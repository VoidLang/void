#pragma once

#include "../Instruction.hpp"

#ifdef VOID_INSTRUCTION
namespace Void {
#pragma region INVOKE_STATIC
    /**
     * Represents an instruction that invokes a static class method.
     */
    class InvokeStatic : public Instruction {
    private:
        /**
         * The name of the target class.
         */
        String className;

        /**
         * The reference of the target class.
         */
        Class* classRef = nullptr;

        /**
         * The name of the target class.
         */
        String methodName;

        /**
         * The parameters of the target method.
         */
        List<String> methodParameters;

        /**
         * The reference of the target method.
         */
        Method* methodRef = nullptr;

    public:
        /**
         * Initialize static method invoke instruction.
         */
        InvokeStatic();

        /**
         * Parse raw bytecode instruction.
         * @param raw bytecode data
         * @parma args split array of the data
         * @param line bytecode line index
         * @param executable bytecode executor
         */
        void parse(String data, List<String> args, uint line, Executable* executable) override;

        /**
         * Initialize the references in the const pool after the whole program has been parsed.
         * @param vm running virtual machine
         * @param executable bytecode executor
         */
        void initialize(VirtualMachine* vm, Executable* executable) override;

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