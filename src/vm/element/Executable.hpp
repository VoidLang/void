#pragma once

#include "../VirtualMachine.hpp"
#include "../runtime/Modifier.hpp"
#include "../parser/Instruction.hpp"

#ifndef VOID_EXECUTABLE
#define VOID_EXECUTABLE
namespace Void {
    class VirtualMachine;
    class Class;
    class Instruction;
    class Instance;

    /**
     * Represents an object in hte virtual machine that is 
     * able to execute bytecode at runtime.
     */
    class Executable {
    public:
        /**
         * The running virtual machine.
         */
        VirtualMachine* vm;

        /**
         * THe partent class of the executable. 
         */
        Class* clazz;

        /**
         * The access modifiers of the executable.
         */
        int modifiers;
    
        /**
         * The list of the executable bytecode instructions. 
         */
        List<Instruction*> bytecode;

        /**
         * The map of the sections which link up section names with
         * their corresponding line in the executable bytecode.
         */
        Map<String, uint> sections;

        /**
         * The map of the linkers that link up variable names with
         * their corresponding storage unit indices.
         */
        Map<String, uint> linkers;

        /**
         * Initialize the virtual machine.
         * @param modifiers executable access modifiers
         * @param vm running virtual machine
         * @param clazz parent class
         */
        Executable(List<String> modifiers, VirtualMachine* vm, Class* clazz);

        /**
         * Build the content of the executable.
         * @param bytecode executable bytecode
         */
        void build(List<String> bytecode);
    
        /**
         * Initialize the const pool references for the executable instructions.
         */
        void initalize();

        /**
         * Determine if the given section name is in use.
         * @param section section key
         * @return true if the section is set
         */
        bool hasSection(String section);

        /**
         * Get the value of the given section.
         * @param section section key
         * @return the line index of the section
         */
        uint getSection(String section);

        
        /**
         * Determine if the given variable linker name is in use.
         * @param linker variable linker name
         * @return true if the variable linker is set
         */
        bool hasLinker(String linker);
    
        /**
         * Determine if the given storage slot is already bound to a variable linker.
         * @param value variable storage unit
         * @return true if the variable storage slot is already set
         */
        bool hasLinkerValue(uint value);

        /**
         * Get the value of the given variable linker.
         * @param linker variable linker name
         * @return the storage unit of the variable
         */
        uint getLinker(String linker);

        /**
         * Determine if the executable has the given access modifier.
         * @param modifier target access modifier
         * @return true if executable bitmask has the modifier
         */
        bool hasModifier(Modifier modifier);
    };
}
#endif