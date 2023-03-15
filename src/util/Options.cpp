#include "Options.hpp"

namespace Void {
    /**
     * Initialize the options parser.
     */
    Options::Options(int argc, char** argv) {
        // declare variables for argument parsing
        String key = "";

        bool lastWasKey = false;
        bool argsStarted = false;
        bool argsRequested = false;

        // parse the program arguments
        // skip the first argument, because that is the file path
        for (int i = 1; i < argc; i++) {
            // get the current argument
            String arg = argv[i];

            // handle program arguments that were put after '-run <file>'
            if (argsStarted) {
                arguments.push_back(arg);
                continue;
            }

            // test if the current argument is a key
            bool isKey = arg[0] == '-';

            // handle key declaration
            if (isKey) {
                // if the key follows a key, the previous key has no value
                if (lastWasKey) {
                    // set the data and reset the key
                    data[key] = "";
                    key = "";
                }

                // remove the prefix of the key
                key = arg.substr(1);

                // handle the last argument
                if (i == argc - 1) {
                    data[key] = "";
                    key = "";
                }

                // handle the start of program arguments declaration
                else if (key == "run")
                    argsRequested = true;
            }

            // handle value declaration
            else {
                // set the key and value and reset the key
                data[key] = arg;
                key = "";
                // start the argument declaration if the key requested it
                if (argsRequested)
                    argsStarted = true;
            }
            // update last key state
            lastWasKey = isKey;
        }
    }

    /**
     * Determine if the key is present in the data.
     */
    bool Options::has(String key) {
        return data.count(key);
    }

    /**
     * Get the value of the key in the data.
     */
    String Options::get(String key) {
        return data[key];
    }
}
