#include "Program.hpp"

#include "../../util/Files.hpp"
#include "../../util/Strings.hpp"

namespace Void {
    /**
     * Initialize the program.
     * @param path void executable pathh
     * @param argument program start arguments
     */
    Program::Program(String path, List<String> arguments) 
        : path(path), arguments(arguments) 
    { }

    /**
     * Validate that the target path is a void executable or a folder.
     */
    bool Program::validate() {
        // validate that the executable path exists
        if (!fileExists(path))
            return false;
        // make sure that the path is either a folder that may contain
        // void executables, or the path is a void executable file
        return Path(path).extension() == ".v";
    }

    /**
     * Read the content from the application path and build bytecode instructions.
     */
    List<String> Program::build() {
        // declare a list to store the raw bytecode instructions into
        List<String> result;

        // test if the target path is a directory
        if (Files::isDirectory(path)) {
            // recursively walk through the files inside the folder
            List<Path> files;
            Files::walk(path, files);

            // compile the files in the folder
            for (Path path : files) {
                // handle void source file
                if (path.extension() == ".v")
                    buildSource(path.generic_string(), result);
                // TODO handle void resource file
            }
        }

        // handle void source file
        else
            buildSource(path, result);

        return result;
    }

    /**
     * Read a void source file and put the parsed instructions in the result.
     */
    void Program::buildSource(String file, List<String>& result) {
        // read the content of the file
        List<String> lines = Files::readLines(file);

        // parse the raw bytecode lines
        for (String line : lines) {
            // ignore lines that are empty or comments
            if (line.length() == 0 || line[0] == ';' || line.find_first_not_of(' ') == String::npos)
                continue;

            // get the actual beginning of the line ignoring whitespaces
            int begin = 0;
            for (ulong i = 0; i < line.length(); i++) {
                // discontinue searching if the current char is a non-whitespace-character
                char c = line[i];
                if (c != ' ' && c != '\t')
                    break;
                // character is whitespace, increment beginning
                begin++;
            }

            // remove all whitespaces from the beginning of the line
            if (begin > 0)
                line = line.substr(begin);

            // split the instruction line
            List<String> args = Strings::split(line, ' ');

            // handle definitions
            if (args[0] == "#define") {
                // get the definition key
                
            }

            // handle main path declaration
            else if (args[0] == "#main") {

            }

            // apppend modifier bytecode
            result.push_back(line);
        }

    }
}