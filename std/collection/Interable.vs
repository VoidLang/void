package "collection"

/**
 * Represents an interface that allows objects to be iterated over.
 * This ensures, that the implementing objects can ne used in for-each statements.
 *
 * # Examples
 * ```
 * for (let element in myIterable)
 *     processElement(element)
 * ```
 *
 * @since 1.0
 */
public:
class Iterable<T> {
    /**
     * Retrieve an iterator over elements of type T.
     * @return a new iterator of T
     */
    Iterator<T> iter()

    /**
     * Perform the given action for each element of this iterable.
     * 
     * The iteratinon stops if all elements have been processed or the action throws an exception.
     * By default, the elements are processed in the order of the iteration.
     *
     * @param action a function to ba called for each elements
     */
    default void forEach(|T| action) {
        for (T element in this)
            action(element)
    }
}
