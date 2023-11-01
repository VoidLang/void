#pragma once

#include "../Common.hpp"

namespace Void {
    /**
     * Represents a command line argument options parser.
     */
    class Options {
    private:
        /**
         * The program arguments data.
         */
        Map<String, String> data;

    public:
        /**
         * The program start arguments.
         */
        List<String> arguments;

        /**
         * Initialize the options parser.
         */
        Options(int argc, char** argv);

        /**
         * Determine if the key is present in the data.
         */
        bool has(String key);

        /**
         * Get the value of the ky in the data.
         */
        String get(String key);
    };
}
