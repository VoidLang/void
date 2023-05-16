package "collection"

/**
 * Represents an iterator over a collection of elements.
 * 
 * This allows iterables to be processed using the for-each loop.
 * Elements can be removed during the processing of the loop.
 *
 * # Examples
 * ```
 * let fruits = ["Oranges", "Bananas", "Oranges"]
 * let iter = fruits.iterator()
 * while (iter.more())
 *     println(iter.next())
 * ```
 * 
 * @since 1.0
 */
public:
interface Iterator<E> {
    /**
     * Indicate, whether the iteration has more elements.
     *
     * @return true if there are more elements to be handled
     */
    bool more()

    /**
     * Retrieve the next element of the iteration wrapped in an option, 
     * that is empty if the iterator does not have more elements.
     *
     * @return the next iterator element
     */
    Option<E> next()

    /**
     * Remove the last element returned by this iterator.
     */
    default void remove()

    /**
     * Iterate over the remaining elements of the iterator.
     *
     * @param action a function to be applied for each remaining elements
     */
    default void remaining(|E| action) {
        while (more())
            action(next())
    }
}
