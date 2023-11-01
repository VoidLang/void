#include "Field.hpp"
#include "../../util/Strings.hpp"

namespace Void {
    /**
     * Initialize the class field.
     * @param name field name
     * @param type field value type
     * @param modifiers field access modifiers
     * @param clazz field parent class
     * @param vm running virtual machine
     */
    Field::Field(String name, String type, List<String> modifiers, Class* clazz, VirtualMachine* vm) 
        : Executable(modifiers, vm, clazz), name(name), type(Type(type))
    { }

    /**
     * Debug the parsed field and its content.
     */
    void Field::debug() {
        // print some indentation for the field
        print("    ");

        // debug the field modifiers
        List<String> modifiers = parseModifiers(this->modifiers);
        if (!modifiers.empty())
            print(Strings::join(modifiers, " ") << ' ');
    
        // debug the field type name and name
        println(type.debug() << ' ' << name << ';');

        // TODO debug bytecode instructions
    }
}
