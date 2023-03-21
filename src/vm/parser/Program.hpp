#pragma once

#include "../../Common.hpp"

namespace Void {

    class Program {
    private:
        /**
         * The path of the executable.
         */
        String path;

        /**
         * The start arguments of the program.
         */
        List<String> arguments;

        /**
         * The map of the program definitions that replaces aliases with keywords.
         */
        Map<String, String> definitions;
        
    public:
        /**
         * The fully qualified path of the main method.
         */
        String programMain;

        /**
         * Initialize the program.
         * @param path void executable pathh
         * @param argument program start arguments
         */
        Program(String path, List<String> arguments);

        /**
         * Validate that the target path is a void executable or a folder.
         * @return true if the program path is valid
         */
        bool validate();

        /**
         * Read the content from the application path and build bytecode instructions.
         * @return the bytecode content of the executable
         */
        List<String> build();

        /**
         * Determine if the given definition key is registered.
         * @param definition definition key
         * @return true if the definition value is set
         */
        bool hasDefinition(String definition);

        /**
         * Get the value of the given definition.
         * @param definition definition key
         * @return definition value or <unknown>
         */
        String getDefinition(String definiton);

        /**
         * Set the value of the given definition.
         * @param definition definition key
         * @param value definition value
         */
        void setDefinition(String definition, String value);

    private:
        /**
         * Read a void source file and put the parsed instructions in the result.
         */
        void buildSource(String file, List<String>& result);
    };
}
