package "lang"

/**
 * Represents the root class of the class hierarchy.
 * Every class implements the methods of Object, including arrays.
 * @since 1.0
 */
public:
class Object {
    /**
     * Retrieve a unique hash for this object.
     * This hash is used by hash table implementations.
     * It provides a per-object hash, therefore you can rely on this value.
     * @return a unique hash for this object
     */
    int hashCode() {
        return memaddr(this)
    }

    /**
     * Retrieve the string representation of this object.
     * The result should be a simple, but detailed debug information of this object.
     * It is recommended for all classes to implement this method.
     * By default, toString() returns the type and memory address the object.
     * @return object debug information
     */
    string toString() {
        return $"<class {typeof(this)} at {memaddr(this)}>"
    }

    /**
     * Indicate whether the given object is equal to this object.
     * This method features an equivalence check for non-null references.
     * By default, this method checks the equivalence of the address of the two objects.
     * For specific equivalence checks, this method should be overridden.
     * @param other object to be compared to this
     * @return true if the two objects are equal
     */
    bool equals(Object other) {
        return this == other
    }
}
