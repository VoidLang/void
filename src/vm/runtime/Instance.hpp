#pragma once

#include "../../Common.hpp"
#include "../element/Field.hpp"
#include "Type.hpp"

#ifndef VOID_INSTANCE
#define VOID_INSTANCE
namespace Void {
    class Field;
    class Class;
    class VirtualMachine;
    class Stack;

    /**
     * The instance identifier incremention counter.
     */
    static int __instanceCounter = 0;

    /**
     * Represents a runtime instance of a loaded class.
     */
    class Instance {
    private:
        /**
         * The map of the non-static class fields and their held values.
         */
        Map<Field*, Object> values;

    public:
        /**
         * The increment identifier of the instance.
         */
        int instanceId = __instanceCounter++;

        /**
         * The type of the instance class.
         */
        Type type;

        /**
         * The instantiated class.
         */
        Class* clazz;

        /**
         * Initialize the instance.
         * @param clazz intantiated class
         */
        Instance(Class* clazz);

        /**
         * Copy non-static class fields into the instance. This is because non-static fields are managed by the instance.
         * @param vm running virtual machine
         * @param stack current stack creating the instance
         * @param reference this instance wrapped in reference
         */
        void copyFields(VirtualMachine* vm, Stack* stack, Reference<Instance*>* reference);

        /**
         * Retrieve a copied field from the value cache.
         * @param name field name
         */
        Field* getField(String name);

        /**
         * Get the value of a copied non-static instance field.
         * @param field target class field
         * @return cached value for the field in the instance
         */
        Object getValue(Field* field);

        /**
         * Set the value of a copied non-static instance field.
         * @param field target class field
         * @param value new field value for the instance
         */
        void setValue(Field* field, Object value);

        /**
         * Get the string representation of the instance.
         * @return instance debug information
         */
        String debug();
    };
}
#endif