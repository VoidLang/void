#pragma once

#include "../../Common.hpp"

namespace Void {
    /**
     * Represents a type wrapper that caches type attributes.
     */
    class Type {
    public:
        /**
         * Determine if the type is a primitive type.
         */
        bool primitive = true;

        /**
         * Determine if the type is an array.
         */
        bool array = false;

        /**
         * The primitive version of the type.
         */
        String primitiveType = "V";

        /**
         * The class version of the type.
         */
        String classType = "Object";

        /**
         * Initialize the type.
         * @param type raw type
         */
        Type(String type);

        /**
         * Test of this type matches another type.
         * @param other other type to test
         * @return true if the two types match
         */
        bool test(Type other);
        
        /**
         * Test of this type matches another type.
         * @param other other raw type to test
         * @return true if the two types match
         */
        bool test(String other);

        /**
         * Get the string representation of the type.
         * @return raw type string
         */
        String debug();
    };

    /**
     * Create an equalence check for two types.
     */
    bool operator==(Type a, Type b);

    /**
     * Create an equalence check for a type and a string.
     */
    bool operator==(Type type, String string);
}
