#pragma once

#include "Executable.hpp"
#include "../runtime/Modifier.hpp"
#include "../../util/Strings.hpp"

namespace Void {
    /**
     * Initialize the virtual machine.
     * @param modifiers executable access modifiers
     * @param vm running virtual machine
     * @param clazz parent class
     */
    Executable::Executable(List<String> modifiers, VirtualMachine* vm, Class* clazz) 
        : vm(vm), clazz(clazz), modifiers(maskModifiers(modifiers))
    { }

    /**
     * Build the content of the executable.
     * @param bytecode executable bytecode
     */
    void Executable::build(List<String> bytecode) {
        // get the section warning options
        bool noWarnings = vm->options.has("XNoWarns");
        bool noSectionWarns = vm->options.has("XNoSectionWarns");
        bool noLinkerWarns = vm->options.has("XNoLinkerWarns");
        bool noDuplicateLinkerWarns = vm->options.has("XNoDupLinkerWarns");


        // preprocess some executable instructions that will be used for other instructions
        // and must be parsed before all the others
        for (uint i = 0; i < bytecode.size(); i++) {
            // parse the current line of the bytecode
            String line = bytecode[i];
            List<String> args = Strings::split(line, ' ');

            // handle jump, sections
            if (line[0] == ':') {
                // parse the name of the section
                String section = line.substr(1);

                // check if the section name is already in use
                if (hasSection(section) && !noWarnings && !noSectionWarns)
                    warn("Duplicate section '" << section << "'.");

                // register the section index
                sections[section] = i;
            }

            // handle variable linkers
            else if (args[0] == "#link") {
                // parse the name of the variable linker
                String variable = args[1];
                // parse the line number of the linker
                uint unit = stringToInt(args[2]);

                // check if the linker name is already in use
                if (hasLinker(variable) && !noWarnings && !noLinkerWarns)
                    warn("Duplicate linker name '" << variable << "'");

                // check if the linker value is already is in use
                if (hasLinkerValue(unit) && !noWarnings && !noLinkerWarns && !noDuplicateLinkerWarns)
                    warn("Duplicate linker value for linker '" << variable << "' = " << unit);

                // register the linker in the executable
                linkers[variable] = unit;
            }
        }

        // after parsing jump sections and variable linkers, let us 
        // preprocess the bytecode instructions, therefore they are 
        // not required to be resolved at runtime
        for (uint i = 0; i < bytecode.size(); i++) {
            // get the current line of the bytecdeo
            String line = bytecode[i];

            // parse the instruction from raw string
            Instruction* instruction = Instruction::of(line, i, this);
            this->bytecode.push_back(instruction);
        }
    }

    /**
     * Initialize the const pool references for the executable instructions.
     */
    void Executable::initalize() {
        // post initialize the instructions after the whole program has been built
        for (Instruction* instruction : bytecode)
            instruction->initialize(vm, this);
    }

    /**
     * Determine if the given section name is in use.
     * @param section section key
     * @return true if the section is set
     */
    bool Executable::hasSection(String section) {
        // loop through the registered jump sections
        for (const auto& [key, value] : sections) {
            // check if the section name matches
            if (key == section)
                return true;
        }
        return false;
    }

    /**
     * Get the value of the given section.
     * @param section section key
     * @return the line index of the section
     */
    uint Executable::getSection(String section) {
        // loop through the registered jump sections
        for (const auto& [key, value] : sections) {
            // check if the section name matches
            if (key == section)
                return value;
        }
        return 0;
    }

    /**
     * Determine if the given variable linker name is in use.
     * @param linker variable linker name
     * @return true if the variable linker is set
     */
    bool Executable::hasLinker(String linker) {
        // loop through the regitered variable linksers
        for (const auto& [key, value] : linkers) {
            // check if the linker name matches
            if (key == linker)
                return true;
        }
        // linker not found
        return false;
    }

    /**
     * Determine if the given storage slot is already bound to a variable linker.
     * @param value variable storage unit
     * @return true if the variable storage slot is already set
     */
    bool Executable::hasLinkerValue(uint value) {
        // loop through the regitered variable linksers
        for (const auto& [key, val] : linkers) {
            // check if the linker value matches
            if (val == value)
                return true;
        }
        // linker not found
        return false;
    }

    /**
     * Get the value of the given variable linker.
     * @param linker variable linker name
     * @return the storage unit of the variable
     */
    uint Executable::getLinker(String linker) {
        // loop through the regitered variable linksers
        for (const auto& [key, value] : linkers) {
            // check if the linker name matches
            if (key == linker)
                return value;
        }
        // linker not found
        return 0;
    }

    /**
     * Determine if the executable has the given access modifier.
     * @param modifier target access modifier
     * @return true if executable bitmask has the modifier
     */
    bool Executable::hasModifier(Modifier modifier) {
        // get the flag of the modifier
        int flag = static_cast<UnderlyingType<Modifier>::type>(modifier);
        // test if the method modifiers mask has the flag
        return (modifiers & flag) > 0;
    }
}
