#include "Type.hpp"

namespace Void {
    /**
     * Initialize the type.
     * @param type raw type
     */
    Type::Type(String type) {
        // test if the type is an array
        if (type[0] == '[') {
            array = true;
            type = type.substr(1);
        }
        // test if the type is a class
        if (type[0] == 'L') {
            primitive = false;
            classType = type.substr(1);
        }
        // type is a primitive
        else
            primitiveType = type;
    }

    /**
     * Test of this type matches another type.
     * @param other other type to test
     * @return true if the two types match
     */
    bool Type::test(Type other) {
        return primitive == other.primitive
            && array == other.array
            && primitiveType == other.primitiveType
            && classType == other.classType;
    }

    /**
     * Test of this type matches another type.
     * @param other other raw type to test
     * @return true if the two types match
     */
    bool Type::test(String other) {
        return test(Type(other));
    }

    /**
     * Get the string representation of the type.
     * @return raw type string
     */
    String Type::debug() {
        StringStream result;
        if (array)
            result << '[';
        if (primitive)
            result << primitiveType;
        else
            result << 'L' << classType;
        return result.str();
    }

    /**
     * Create an equalence check for two types.
     */
    bool operator==(Type a, Type b) {
        return a.test(b);
    }

    /**
     * Create an equalence check for a type and a string.
     */
    bool operator==(Type type, String string) {
        return type.test(string);
    }
}
