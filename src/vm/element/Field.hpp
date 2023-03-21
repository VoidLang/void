#pragma once

#include "../../Common.hpp"
#include "Executable.hpp"
#include "../runtime/Type.hpp"

#ifdef VOID_EXECUTABLE
#ifndef VOID_FIELD
#define VOID_FIELD
namespace Void {
    class Field : public Executable {
    public:
        /**
         * The name of the field.
         */
        String name;

        /**
         * The type of the field.
         */
        Type type;

        /**
         * The held value of the field.
         */
        Object value;

        /**
         * Initialize the class field.
         * @param name field name
         * @param type field value type
         * @param modifiers field access modifiers
         * @param clazz field parent class
         * @param vm running virtual machine
         */
        Field(String name, String type, List<String> modifiers, Class* clazz, VirtualMachine* vm);

        /**
         * Debug the parsed field and its content.
         */
        void debug();
    };
}
#endif
#endif