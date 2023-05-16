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
 * while ((let iter = fruits.iter()).more())
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
     * # Examples
     * ```
     * let numbers = [1, 2, 3]
     * assert numbers.more() == true
     * ```
     *
     * @return true if there are more elements to be handled
     */
    bool more()

    /**
     * Retrieve the next element of the iteration wrapped in an option, 
     * that is empty if the iterator does not have more elements.
     *
     * # Examples
     * ```
     * let numbers = [1, 2, 3]
     * assert numbers.next() == 1
     * assert numbers.next() == 2
     * assert numbers.next() == 3
     * ```
     * 
     * @return the next iterator element
     */
    Option<E> next()

    /**
     * Remove the last element returned by this iterator.
     * 
     * # Examples
     * ```
     * let numbers = [1, 2, 3, 4, 5]
     * 
     * while ((let iter = numbers.iter()).more())
     *     if (iter.next().get() % 2 == 0) 
     *         iter.remove()
     *  
     * assert numbers == [1, 3, 5]
     * ```
     */
    default void remove()

    /**
     * Iterate over the remaining elements of the iterator.
     *
     * # Examples
     * ```
     * let numbers = [1, 2, 3, 4, 5]
     * numbers.next()
     * numbers.next()
     *
     * numbers.remaining(Console::println)
     * ```
     * This code will output:
     * ```
     * 3
     * 4
     * 5
     * ```
     * 
     * @param action a function to be applied for each remaining elements
     */
    default void remaining(|E| action) {
        while (more())
            action(next())
    }
}
