#include "Instance.hpp"

namespace Void {
    /**
     * Initialize the instance.
     * @param clazz intantiated class
     */
    Instance::Instance(Class* clazz)
        : type(Type("L" + clazz->name)), clazz(clazz)
    { }

    /**
     * Copy non-static class fields into the instance. This is because non-static fields are managed by the instance.
     * @param vm running virtual machine
     * @param stack current stack creating the instance
     * @param reference this instance wrapped in reference
     */
    void Instance::copyFields(VirtualMachine* vm, Stack* stack, Reference<Instance*>* reference) {
        // recursively copy non-static fields from the class to this instance
        Class* temp = clazz;
        while (temp != nullptr) {
            // loop through the registered class fields
            for (Field* field : clazz->fields) {
                // skip field if it is already copied
                if (getField(field->name) != nullptr)
                    continue;
                // skip if the field is static
                if (field->hasModifier(Modifier::STATIC))
                    continue;
                // TODO invoke the field
                // put the value in the instance cache
                values[field] = field->value;
            }
        }
    }

    /**
     * Retrieve a copied field from the value cache.
     * @param name field name
     */
    Field* Instance::getField(String name) {
        // loop through the copied fields
        for (const auto& [field, value] : values) {
            // check if the field name matches
            if (field->name == name)
                return field;
        }
        // field not found, return a null field pointer
        return nullptr;
    }

    /**
     * Get the value of a copied non-static instance field.
     * @param field target class field
     * @return cached value for the field in the instance
     */
    Object Instance::getValue(Field* field) {
        // loop through the copied fields
        for (const auto& [key, value] : values) {
            // check if the field name matches
            if (key == field)
                return value;
        }
        // value not found, return a null value pointer
        return nullptr;
    }

    /**
     * Set the value of a copied non-static instance field.
     * @param field target class field
     * @param value new field value for the instance
     */
    void Instance::setValue(Field* field, Object value) {
        values[field] = value;
    }

    /**
     * Get the string representation of the instance.
     * @return instance debug information
     */
    String Instance::debug() {
        // get the address of the instance
        const void* address = static_cast<const void*>(this);

        // create the instance debug message
        StringStream stream;
        stream << "<class " << clazz->name << " at 0x " << address << " id " << instanceId << ">";

        return stream.str();
    }
}