package "lang"

/**
 * Represents a resizable-array-based implementation of the Collection interface.
 */
public:
class List<E> : Collection<E> {
    /**
     * Retrieve the number of elements in this list.
     * @return list element count
     */
    uint size();

    /**
     * Indicate whether the list contains no elements.
     * @return true if the list is empty
     */
    bool empty();

    /**
     * Indicate whether the list contains the specified element.
     * @param element target element whose presence is tested
     * @return true if this list contains the specified element
     */
    bool has(E element)

    /**
     * Retrieve the element at the specified index in this list.
     * @param index target position index
     * @return the element at the specified index
     */
    E get(uint index)

    /**
     * Replace the element at the specified index with the specified element.
     * @param index target position index
     * @return the previous element at the specified index
     */
    E set(uint index, E element)

    /**
     * Append the specified element to the end of this list.
     * @param element target element to be added
     */
    void add(E element)

    /**
     * Insert the specified element to the specified  index of this list.
     * @param index specified index to insert to
     * @param element target element to be added 
     */
    void add(uint index, E element)

    /**
     * Remove all occurences of the specified element from the list.
     * @param element target element to be removed
     * @return true if any elements were removed
     */
    bool remove(E element)

    /**
     * Remove the first occurence of the specified element from the list.
     * @param element target element to be removed
     * @return true if the element was removed
     */
    bool removeFirst(E element)

    /**
     * Remove the last occurence of the specified element from the list.
     * @param element target element to be removed
     * @return true if the element was removed
     */
    bool removeLast(E element)

    /**
     * Remove an element of the list at the specified index.
     * @param index target index to be removed from
     * @return the element that has been removed
     */
    E pop(uint index)

    /**
     * Remove all elements of the list.
     */
    void clear()

    /**
     * Find the index of the first occurence of the specified element in the list.
     * @param element target element to be searched for
     * @return the index of the element or -1 if it is not in the list
     */
    uint indexOf(E element)

    /**
     * Find the index of the last occurence of the specified element in the list.
     * @param element target element to be searched for
     * @return the index of the element or -1 if it is not in the list
     */
    uint lastIndexOf(E element)
}
