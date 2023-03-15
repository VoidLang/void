#include "Common.hpp"

#include "util/Options.hpp"

namespace Void {
    /**
     * Represents a command line interaction interface that allows the user to create a 
     * new project, compile sources, generate native headers, and much more.
     */
    class Launcher {
        /**
         * The current version of the build.
         */
        const String VERSION = "1.0.1-BETA";

    public:
        /**
         * Launch the void program and process user input.
         * @param argc argument count
         * @param argv argument data
         */
        void start(int argc, char** argv);

    private:
        /**
         * Print the void usage help message to the console.
         */
        void sendHelp();
    
        /**
         * Launch a compiled void executable application.
         * @param options command line arguments
         */
        void launchProgram(Options& options);

        /**
         * Compiule project source code to a void executable.
         * @param options command line arguments
         */
        void compileSources(Options& options);

        /**
         * Generate a native header for a compile void class.
         * @param options command line arguments
         */
        void generateHeader(Options& options);
    };
}
