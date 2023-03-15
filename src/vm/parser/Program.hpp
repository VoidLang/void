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
         * Initialize the program.
         * @param path void executable pathh
         * @param argument program start arguments
         */
        Program(String path, List<String> arguments);

        /**
         * Validate that the target path is a void executable or a folder.
         */
        bool validate();

        /**
         * Read the content from the application path and build bytecode instructions.
         */
        List<String> build();

    private:
        /**
         * Read a void source file and put the parsed instructions in the result.
         */
        void buildSource(String file, List<String>& result);
    };
}