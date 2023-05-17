package "collection"

/**
 * Represents a resizable-array-based implementation of the Collection interface.
 * 
 * # Examples
 * ```
 * let list = [1, 2, 3]
 * list.add(4)
 * list.add(5)
 * 
 * assert list == [1, 2, 3, 4, 5]
 * ```
 * 
 * @since 1.0
 */
public:
class List<E> : Collection<E> {
    /**
     * Retrieve the number of elements in this list.
     * 
     * # Examples
     * ```
     * let numbers = [10, 20, 30]
     * assert numbers.size() == 3
     * ```
     * 
     * ```
     * let numbers = [1, 2, 3, 4, 5]
     * assert numbers.size() == 5
     * ```
     * 
     * @return list element count
     */
    native uint size();

    /**
     * Indicate whether the list contains no elements.
     * 
     * # Examples
     * ```
     * let list = []
     * assert list.empty() == true
     * ```
     *
     * ```
     * let list = ["hello", "world"]
     * assert list.empty() == false
     * ```
     * 
     * @return true if the list is empty
     */
    native bool empty();

    /**
     * Indicate whether the list contains the specified element.
     * 
     * # Examples
     * ```
     * let numbers = [1, 2, 3]
     * assert numbers.has(2) == true
     * assert numbers.has(7) == false
     * ```
     * 
     * @param element target element whose presence is tested
     * @return true if this list contains the specified element
     */
    native bool has(E element)

    /**
     * Retrieve the element at the specified index in this list.
     * 
     * # Examples
     * ```
     * let numbers = [11, 22, 33]
     * assert numbers.get(0).unwrap() == 11
     * assert numbers.get(1).unwrap() == 22
     * assert numbers.get(2).unwrap() == 33
     * ```
     * 
     * @param index target position index
     * @return the element at the specified index wrapped in an option, 
     * that is empty if there is no element at the specified index
     */
    native Option<E> get(uint index)

    /**
     * Replace the element at the specified index with the specified element.
     * 
     * # Examples
     * ```
     * let numbers = [40, 20, 30]
     * numbers.set(0, 10)
     * 
     * assert numbers == [10, 20, 30]
     * ```
     * 
     * @param index target position index
     * @return the previous element at the specified index wrapped in an option, 
     * that is empty if there was no element at the previous index
     */
    native Option<E> set(uint index, E element)

    /**
     * Append the specified element to the end of this list.
     * 
     * # Examples
     * ```
     * let numbers = [1, 2]
     * numbers.add(3)
     * 
     * assert numbers == [1, 2, 3]
     * ```
     * 
     * @param element target element to be added
     */
    native void add(E element)

    /**
     * Insert the specified element to the specified  index of this list.
     * 
     * # Examples
     * ```
     * let numbers = [2, 3]
     * numbers.add(0, 1)
     * 
     * assert numbers == [1, 2, 3]
     * ```
     * 
     * @param index specified index to insert to
     * @param element target element to be added 
     */
    native void add(uint index, E element)

    /**
     * Remove all occurences of the specified element from the list.
     * 
     * # Examples
     * ```
     * let numbers = [1, 2, 3, 5]
     * numbers.remove(5)
     * 
     * assert numbers == [1, 2, 3]
     * ```
     * 
     * @param element target element to be removed
     * @return true if any elements were removed
     */
    native bool remove(E element)

    /**
     * Remove the first occurence of the specified element from the list.
     * 
     * # Examples
     * ```
     * let numbers = [3, 1, 2, 3]
     * numbers.removeFirst(3)
     * 
     * assert numbers == [1, 2, 3]
     * ```
     * 
     * @param element target element to be removed
     * @return true if the element was removed
     */
    native bool removeFirst(E element)

    /**
     * Remove the last occurence of the specified element from the list.
     * 
     * # Examples
     * ```
     * let numbers = [3, 1, 2, 3]
     * numbers.removeLast(3)
     * 
     * assert numbers == [3, 1, 2]
     * ```
     * 
     * @param element target element to be removed
     * @return true if the element was removed
     */
    native bool removeLast(E element)

    /**
     * Remove an element of the list at the specified index.
     *
     * # Examples
     * ```
     * let numbers = [1, 2, 3]
     * numbers.pop(1)
     * 
     * assert numbers == [1, 3]
     * ```
     * 
     * @param index target index to be removed from
     * @return the element that has been removed wrapped in an option,
     * that is empty if there was no element at the specified index
     */
    native Option<E> pop(uint index)

    /**
     * Remove all elements of the list.
     * 
     * # Examples
     * ```
     * let numbers == [1, 2, 3]
     * numbers.clear()
     * 
     * assert number.empty() == true
     * ```
     */
    native void clear()

    /**
     * Find the index of the first occurence of the specified element in the list.
     * 
     * # Examples
     * ```
     * let numbers = [10, 20, 30]
     * assert numbers.indexOf(10) == 0
     * assert numbers.indexOf(20) == 1
     * assert numbers.indexOf(30) == 2
     * ```
     * 
     * @param element target element to be searched for
     * @return the index of the element or -1 if it is not in the list
     */
    native uint indexOf(E element)

    /**
     * Find the index of the last occurence of the specified element in the list.
     * 
     * # Examples
     * ```
     * let numbers = [1, 2, 3, 1]
     * assert numbers.lastIndexOf(1) == 3
     * ```
     * 
     * @param element target element to be searched for
     * @return the index of the element or -1 if it is not in the list
     */
    native uint lastIndexOf(E element)
}
