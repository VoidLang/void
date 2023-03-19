#include "VirtualMachine.hpp"

#include "../util/Strings.hpp"
#include "../util/Lists.hpp"
#include "parser/Instruction.hpp"

namespace Void {
    /**
     * Initialize the virtual machine.
     * @param options command line options
     */
    VirtualMachine::VirtualMachine(Options& options)
        : options(options)
    { }

    /**
     * Load bytecode to the virtual machine dynamically.
     * @param bytecode raw bytecode to load
     */
    void VirtualMachine::loadBytecode(List<String> bytecode) {
        // the name of the parsed class
        String name = "<unk>";
        // the superclass of the parsed class
        String superclass = "Object";

        // the modifiers of the parsed class
        List<String> modifiers;
        // the interfaces of the parsed class
        List<String> interfaces;

        // the content of the parsed class, to be handled by the class intself
        List<String> content;

        // determine if the declaration of the content of the parsed class begun
        bool contentBegun = false;

        // the offset of inner classes inside the content
        // to be incremented by every CLASS_BEGIN
        // to be decremented by every CLASS_END
        uint classOffset = 0;

        // parse the raw bytecode instructions
        for (String line : bytecode) {
            // split up the raw instruciton line
            List<String> args = Strings::split(line, ' ');
            String instruction = args[0];

            // check if the class content declaration has begun
            if (contentBegun) {
                // handle class content declaration end
                if (instruction == Instructions::CLASS_END && --classOffset == 0) {
                    // mark the class declaration ended
                    contentBegun = false;

                    // check if the class name is already in use
                    if (getClass(name) != nullptr)
                        error("ClassRedefineException: Class '" << name << "' is already defined.");

                    // define the class in the virtual machine
                    Class* clazz = new Class(name, superclass, modifiers, interfaces, this);
                    defineClass(clazz);
                    // make the class build its content
                    clazz->build(content);

                    // reset the class declaration variables
                    name = "<unk>";
                    superclass = "Object";
                    modifiers.clear();
                    interfaces.clear();
                    content.clear();
                }

                // handle inner class declaration begin
                else {
                    // increment the inner class offset
                    if (instruction == Instructions::CLASS_BEGIN)
                        classOffset++;
                    // append the line to the class content
                    content.push_back(line);
                }
            }

            // handle class definition start
            else if (instruction == Instructions::CLASS_DEFINE)
                name = args[1];

            // set the class modifiers
            else if (instruction == Instructions::CLASS_MODIFIERS)
                modifiers = Lists::subList(args, 1);

            // set the class superclass
            else if (instruction == Instructions::CLASS_EXTENDS)
                superclass = args[1];

            // set the clsas interfaces
            else if (instruction == Instructions::CLASS_IMPLEMENTS)
                interfaces = Lists::subList(args, 1);

            // handle class content declaration begin
            else if (instruction == Instructions::CLASS_BEGIN && classOffset++ == 0)
                contentBegun = true;
        }
    }

    /**
     * Debug the runtime data of the virtual machine.
     */
    void VirtualMachine::debug() {
        for (Class* clazz : classes)
            clazz->debug();
    }

    /**
     * Retrieve a loaded class by its name.
     * @param name class anme
     * @param class retrieved class or nullptr if missing
     */
    Class* VirtualMachine::getClass(String name) {
        // loop through the loaded classes
        for (Class* clazz : classes) {
            // check if the class name matches the test
            if (clazz->name == name)
                return clazz;
        }
        // class not found, return null class 
        return nullptr;
    }

    /**
     * Define a new class in the virtual machine.
     * @param class class to add
     */
    void VirtualMachine::defineClass(Class* clazz) {
        classes.push_back(clazz);
    }
}
