#include "Launcher.hpp"

namespace Void {
    /**
     * Launch the void program and process user input.
     * @param argc argument count
     * @param argv argument data
     */
    void Launcher::start(int argc, char** argv) {
        // send help message if there are not enough arguments
        if (argc < 2) {
            sendHelp();
            return;
        }


    }

    /**
     * Print the void usage help message to the console.
     */
    void Launcher::sendHelp() {
        println("Void v" << VERSION);
        println("Usage: void [options] [args...]" << '\n');
        println("Arguments following the -run <file> are passed as the arguments to the main method." << '\n');
        println("Where options include:" << '\n');
        println("	-run <executable file>		Execute a compiled vertex program.");
        println("	-compile <project folder>	Compile vertex source files.");
        println("	-header <source file>		Create a c++ header for the given source file.");
        println("");
    }
}
