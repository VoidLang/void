#include "Launcher.hpp"

#include "vm/parser/Program.hpp"
#include "vm/VirtualMachine.hpp"
#include "vm/element/Executable.hpp"
#include "vm/runtime/Stack.hpp"
#include "vm/element/Method.hpp"
#include "vm/element/Field.hpp"

#include "util/Files.hpp"

#include "compiler/token/Token.hpp"
#include "compiler/token/Tokenizer.hpp"
#include "compiler/token/Transformer.hpp"
#include "compiler/Project.hpp"
#include "compiler/node/NodeParser.hpp"

using namespace Compiler;

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
        println("   -new <project name>         Create a new Void project.");
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

        // check if the main path was not specified
        if (program.programMain.empty())
            error("Main method in not specified.");

        // get the main class of the program
        Class* mainClass = vm->getClass(program.programMain);
        if (mainClass == nullptr) 
            error("NoClassFoundException: No such class " << program.programMain);
    
        // get the main method
        Method* mainMethod = mainClass->getMethod("main", List<String>());
        if (mainMethod == nullptr)
            error("NoSuckMethodException: No such method " << mainClass->name + ".main()V");
    
        // create the heap stack
        Stack* heap = new Stack(nullptr, nullptr, "Heap");

        // call static constructors and initialize static fields
        vm->initialize(heap);

        // TODO setup program arguments for the environment

        auto begin = currentTimeMillis();
        mainMethod->invoke(vm, heap, nullptr, nullptr);
        auto end = currentTimeMillis();

        println("");
        println("Executed in " << end - begin << "ms");
    }

    /**
     * Compiule project source code to a void executable.
     * @param options command line arguments
     */
    void Launcher::compileSources(Options& options) {
        println("Compiling sources " << options.get("compile"));

        // check for correct command usage
        if (!options.has("compile"))
            error("Usage: void -compile <project folder> -out <output file path>");

        // get the input root directory of the project
        String inputDir = options.get("compile");
        println("Compiling project root " << inputDir);

        // create the void application wrapper
        Project project(inputDir);
        // validate that the project files are exist
        // project.validate();

        Tokenizer tokenizer(Files::readUTF(inputDir));

        List<Token> tokens;

        while (true) {
            Token token = tokenizer.next();
            if (!token.hasNext()) 
                break;
            tokens.push_back(token);
            println(std::setw(12) << token);
        }

        println("\n---\n");

        Transformer transformer(tokens);

        tokens = transformer.transform();

        for (Token token : tokens) 
            println(std::setw(12) << token);
        
        NodeParser parser(tokens);
        while (true) {
            Compiler::Node node = parser.next();

            if (node.type == NodeType::Error)
                error("Error!");
        }
    }

    /**
     * Generate a native header for a compile void class.
     * @param options command line arguments
     */
    void Launcher::generateHeader(Options& options) {
        println("Generating headers " << options.get("header"));
    }
}
