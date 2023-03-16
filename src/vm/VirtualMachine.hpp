#pragma once

#include "../Common.hpp"
#include "../util/Options.hpp"
#include "element/Class.hpp"

namespace Void {
    class Class;

    /**
     * Represents a high-level application environment emulator.
     * Loads executable bytecode dynamically.
     */
    class VirtualMachine {
    private:
        /**
         * The command line options of the application.
         */
        Options& options;

        /**
         * The list of the runtime loaded classes.
         */
    private:
        List<Class*> classes;
    
    public:
        /**
         * Initialize the virtual machine.
         * @param options command line options
         */
        VirtualMachine(Options& options);

        /**
         * Load bytecode to the virtual machine dynamically.
         * @param bytecode raw bytecode to load
         */
        void loadBytecode(List<String> bytecode);

        /**
         * Debug the runtime data of the virtual machine.
         */
        void debug();

        /**
         * Retrieve a loaded class by its name.
         * @param name class anme
         * @param class retrieved class or nullptr if missing
         */
        Class* getClass(String name);

        /**
         * Define a new class in the virtual machine.
         * @param class class to add
         */
        void defineClass(Class* clazz);
    };
}
