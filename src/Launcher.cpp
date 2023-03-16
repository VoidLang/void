#include "Launcher.hpp"
#include "vm/parser/Program.hpp"
#include "vm/VirtualMachine.hpp"

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

        // parse the program arguments
        Options options(argc, argv);

        // launch a compiled void executable
        if (options.has("run"))
            launchProgram(options);
        // compile source code to executable
        else if (options.has("compile"))
            compileSources(options);
        // generate a native header for a compiled void executable
        else if (options.has("header"))
            generateHeader(options);
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

    /**
     * Launch a compiled void executable application.
     * @param options command line arguments
     */
    void Launcher::launchProgram(Options& options) {
        println("Running executable " << options.get("run"));

        // get the path of the executable file
        String path = options.get("run");

        // create a program that will read the raw bytecode from a file or folder
        Program program(path, options.arguments);

        // read the bytecode from the file path
        List<String> bytecode = program.build();
        for (String line : bytecode) 
            println("> " << line);

        // create the virtual machine
        // make the virtual machine load application elements 
        // pre-parse all the classes, fields and methods
        VirtualMachine* vm = new VirtualMachine(options);
        vm->loadBytecode(bytecode);

        // debug data of the virtual machine
        if (options.has("XVMDebug")) {
            println("[Void] Virtual Machine debug output:");
            vm->debug();
        }
    }

    /**
     * Compiule project source code to a void executable.
     * @param options command line arguments
     */
    void Launcher::compileSources(Options& options) {
        println("Compiling sources " << options.get("compile"));
    }

    /**
     * Generate a native header for a compile void class.
     * @param options command line arguments
     */
    void Launcher::generateHeader(Options& options) {
        println("Generating headers " << options.get("header"));
    }
}
