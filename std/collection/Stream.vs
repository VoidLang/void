package "collection"

/**
 * Represents a lazy iterable transformer of a sequence of elements.
 *
 * # Examples
 * ```
 * let test = ["1", "hello", "2", "four", "3"]
 * let numbers = test
 *     .stream()
 *     .filterMap(int::parse)
 *     .collect()
 * assert numbers == [1, 2, 3]
 * ```
 * 
 * @since 1.0
 */
public:
interface Stream<T> {
    /**
     * Retrieve a stream consisting of the elements of this stream that match the specified predicate.
     * 
     * # Examples
     * ```
     * let nums = [-1, 1, -2, 2, -3, 3]
     * let nums = nums
     *     .stream()
     *     .filter(|x| x > 0)
     *     .collect()
     * assert nums = [1, 2, 3]
     * ```
     * 
     * @param predicate a function that determines whether to include an element in the stream
     * @return a new stream of the filtered elements
     */
    Stream<T> filter(bool |T| predicate)

    /**
     * Retrieve a stream consisting of the elements of this stream that match the specified predicate.
     * 
     * This operation will discard all elements, which produce an empty optional.
     * 
     * # Examples
     * ```
     * let test = ["1", "hello", "2", "four", "3"]
     * let numbers = test
     *     .stream()
     *     .filterMap(|x| int.parse().ok())
     *     .collect()
     * assert numbers == [1, 2, 3]
     * ```
     *
     * @param mapper a function that tries to map the elements of the stream
     * @return a stream of the elements which were able to transform
     */
    Stream<U> filterMap<U>(Option<U> |T| mapper)

    /**
     * Retrieve a stream consisting of the elements of this stream that match the specified predicate.
     * 
     * This operation will discard all elements, which produce an error result..
     * 
     * # Examples
     * ```
     * let test = ["1", "hello", "2", "four", "3"]
     * let numbers = test
     *     .stream()
     *     .filterMap(int::parse)
     *     .collect()
     * assert numbers == [1, 2, 3]
     * ```
     *
     * @param mapper a function that tries to map the elements of the stream
     * @return a stream of the elements which were able to transform
     */
    Stream<U> filterMap<U>(Result<U> |T| mapper)

    /**
     * Retrieve a stream consisting of the results of applying the specified mapper to the elements of this stream.
     * 
     * # Examples
     * ```
     * struct Person(string name)
     * 
     * let people = [
     *     new Person("John Doe"),
     *     new Person("Jane Doe")
     * ]
     * let names = people
     *     .stream()
     *     .map(|person| person.name)
     *     .collect()
     * assert names == ["John Doe", "Jane Doe"]
     * ```
     * 
     * @param mapper a function that transforms the T origin to a U type
     * @return a new stream of the transformer elements
     */
    Stream<U> map<U>(U |T| mapper)

    /**
     * Create a new stream that chains this stream and the specified stream together.
     * 
     * `chain()` will return a new stream that will first iterate over the values from the first stream,
     * then iterate over the values from the second stream.
     *
     * # Examples
     * ```
     * let first = [1, 2, 3]
     * let second = [4, 5, 6]
     * 
     * let numbers = first
     *     .stream()
     *     .chain(second.stream())
     *     .collect()
     *
     * assert numbers == [1, 2, 3, 4, 5, 6]
     * ```
     * 
     * @param other a stream to be chained with this stream
     * @return a new stream consisting this stream and the specified stream
     */
    Stream<T> chain(Iterator<T> other)

    /**
     * Fold every element into an accumulator by applying an operation, returning the final result.
     * 
     * This is equvivalent to:
     * ```
     * T result = init
     * for (T element in this stream)
     *     result = accumulator(result, element)
     * return result
     * ```
     * 
     * # Examples
     * ```
     * int sum = numbers.fold(0, |acc, x| acc + x)
     * ```
     * or
     * ```
     * int sum = numbers.fold(0, int::sum)
     * ```
     * 
     * @param init the initial value for the accumulating function
     * @param accumulator an associative function for combining two values
     * @return the result of the accumulation
     */    
    T fold(T init, T |T, T| accumulator)

    /**
     * Fold the stream and retrieve the count of elements in it.
     *
     * # Examples
     * ```
     * let numbers = [1, 2, 3]
     * assert numbers.stream().count() == 3
     * ```
     * 
     * @return the count of elements the stream consists
     */
    long count()

    /**
     * Determine if any element of the iterator matches a predicate.
     *
     * # Examples
     * ```
     * let numbers = [1, 2, -3, 4]
     *
     * let hasNegative = numbers
     *     .stream()
     *     .any(|x| x < 0)
     * 
     * assert hasNegative == true
     * ```
     *
     * ```
     * let numbers = [5, 6, 7, 8]
     * 
     * let hasNegative = numbers
     *     .stream()
     *     .any(|x| x < 0)
     *
     * assert hasNegative == false
     * ```
     *
     * @param predicate a function to test if an element matches a condition
     * @return true if the predicate matches any element
     */
    bool any(bool |T| predicate)

    /**
     * Determine if every element of the iterator matches a predicate.
     *
     * # Examples
     * ```
     * let numbers = [1, 2, 3, 4, 5]
     * 
     * let allEven = numbers
     *     .stream()
     *     .all(|x| x % 2 == 0)
     * 
     * assert allEven == false
     * ```
     * 
     * ```
     * let numbers = [2, 4, 6, 8, 10]
     * 
     * let allEven = numbers
     *     .stream()
     *     .all(|x| x % 2 == 0)
     *
     * let allEven == true
     * 
     * @param predicate a function to test if all elements match a condition
     * @return true if the predicate matches any element
     */
    bool all(bool |T| predicate)

    /**
     * Retrieve the minimum element of this stream according to the specified comparator.
     * 
     * This operator folds the stream and retrieves the minimum element.
     * 
     * # Examples
     * ```
     * let weights = [7, 12, 3, 25]
     * 
     * let lightest = weights
     *     .stream()
     *     .min(int::cmp)
     *     .get()
     * 
     * assert lightest == 3
     * ```
     *
     * @param comparator a function to compare elements of this stream
     * @return the minimum element wrapped in an optional, that is empty if the stream is empty
     */
    Option<T> min(int |T, T| comparator)

    /**
     * Retrieve the maximum element of this stream according to the specified comparator.
     * 
     * This operator folds the stream and retrieves the maximum element.
     * 
     * # Examples
     * let weights = [30, 100, 75, 80]
     *
     * let heaviest = weights
     *     .stream()
     *     .max(int::cmp)
     *     .get()
     * 
     * assert heaviest == 100
     * ```
     *
     * @param comparator a function to compare elements of this stream
     * @return the maximum element wrapped in an optional, that is empty if the stream is empty
     */
    Option<T> max(int |T, T| comparator)

    /**
     * Retrieve a stream that skips the first `n` elements.
     * 
     * This operation discards the first `n` elements of this stream.
     * 
     * # Examples
     * ```
     * let numbers = [1, 2, 3, 4, 5]
     * let numbers = numbers.stream().skip(3).collect()
     * 
     * assert numbers == [3, 4, 5]
     * ```
     * 
     * @param n the number of leading elements to skip
     * @return a new stream without the first `n` elements
     */
    Stream<T> skip(int n)    

    /**
     * Retrieve a stream consisting of the elements of this stream, truncated to be no longer than `size`.
     * 
     * This operation discards all elements that exceded the size.
     * 
     * # Examples
     * ```
     * let numbers = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
     * let numbers = numbers.stream().limit(5).collect()
     *
     * assert numbers == [10, 20, 30, 40, 50]
     * ```
     * 
     * @param size the number of elements the stream should be limited to
     * @return a new stream with the specified maximum size
     */
    Stream<T> limit(int size)

    /**
     * Search for the first element in the stream that satisfies the specified predicate.
     * 
     * # Examples
     * ```
     * struct User(string name, int id)
     * 
     * let database = [
     *     new User("John Doe", 101),
     *     new User("Jane Doe", 102)
     * ]
     *
     * let user = database
     *     .findFirst(|user| user.id == 102)
     *     .get()
     *
     * let user.name == "Jane Doe"
     * ```
     * 
     * @param predicate a function to test a condition of the stream elements
     * @return an optional with the first element matching the predicate, 
     * that is empty if no elements matched the condition  
     */
    Option<T> findFirst(bool |T| predicate)

    /**
     * Search for the last element in the stream that satisfies the specified predicate.
     * 
     * # Examples
     * ```
     * struct Book(string author, string title)
     * 
     * let shelf = [
     *     new Book("John Doe", "The Void Programming Language")  
     *     new Book("John Doe", "Does pineapple belong on pizza?")  
     *     new Book("John Doe", "How to write safe code?")
     *     new Book("Jane Doe", "What is async/await")
     * ]
     *
     * // task: find the last book by John Doe
     * let book = shelf
     *     .stream()
     *     .findLast(|book| book.author == "John Doe")
     *     .get()
     *
     * assert book.name == "How to write safe code?"
     * ```
     * 
     * @param predicate a function to test a condition of the stream elements
     * @return an optional with the last element matching the predicate, 
     * that is empty if no elements matched the condition  
     */
    Option<T> findLast(bool |T| predicate)

    /**
     * Search for the nth element in the stream that satisfies the specified predicate.
     * 
     * # Examples
     * ```
     * let numbers = [1, 2, 3, 4, 5, 6]
     *
     * let secondEvenNumber = numbers
     *     .stream()
     *     .findNth(|x| x % 2 == 0, 1)
     *     .get()
     *
     * assert secondEvenNumber == 4
     * ```
     * 
     * @param predicate a function to test a condition of the stream elements
     * @return an optional with the last element matching the predicate, 
     * that is empty if no elements matched the condition  
     */
    Option<T> findNth(bool |T| predicate, int n)

    /**
     * Retrieve the first element of the stream.
     *
     * # Examples
     * ```
     * let fruits = ["Apples", "Bananas", "Oranges"]
     * 
     * assert fruits.first() == "Apples"
     * ```
     * 
     * @return an optional with the first element of the stream, 
     * that is empty if the stream is empty
     */
    Option<T> first()

    /**
     * Retrieve the last element of the stream.
     *
     * # Examples
     * ```
     * let fruits = ["Apples", "Bananas", "Oranges"]
     * 
     * assert fruits.last() == "Oranges"
     * ```
     * 
     * @return an optional with the last element of the stream, 
     * that is empty if the stream is empty
     */
    Option<T> last()

    /**
     * Retrieve the nth element of the stream.
     *
     * # Examples
     * ```
     * let fruits = ["Apples", "Bananas", "Oranges"]
     * 
     * assert fruits.nth(1) == "Bananas"
     * ```
     * 
     * @return an optional with the nth element of the stream, 
     * that is empty if the stream is empty or the index is out of bounds
     */
    Option<T> nth(int n)

    /**
     * Retrieve a stream of the distinct elements of this stream.
     *
     * This operation discards all duplicate elements from the stream.
     *
     * # Examples
     * ```
     * let numbers = [1, 2, 2, 3, 4, 5, 5]
     * let numbers = numbers.stream().unique().collect()
     * assert numbers == [1, 2, 3, 4, 5] 
     * ```
     *
     * @return a new stream without duplicate elements
     */
    Stream<T> unique()

    /**
     * Retrieve a stream of the distinct elements by their specified key of this stream.
     * 
     * The key of each element is given by the extractor function.
     *
     * # Examples
     * ```
     * struct Person(string name)
     * 
     * let people = [
     *     new User("John Doe"),
     *     new User("John Doe"),
     *     new User("Jane Doe")
     * ]
     * people
     *     .stream()
     *     .unique(|person| person.name)
     *     .forEach(|person| println(person.name))
     * ```
     * This code will output:
     * ```
     * John Doe
     * Jane Doe
     * ```
     * 
     * @param extractor a function that exctracts keys from the elements
     * @return a new stream without duplicate elements
     */
    Stream<T> unique<U>(U |T| extractor)

    /** 
     * Retrieve a stream consisting of the elements of this stream, sorted according to natural order.
     * 
     * This operation invokes `Comparator#compare(T, T)` if the elements of this stream implement it.
     * Otherwise elements are ordered by memory addresses.
     *
     * # Examples
     * ```
     * let number = [3, 1, 5, 2, 4]
     * let numbers = numbers.stream().sort().collect()
     * 
     * assert numbers == [1, 2, 3, 4, 5]
     * ```
     * 
     * @return a new stream with ordered elements 
     */
    Stream<T> sort()

    /**
     * Retrieve a stream consisting the elements of this stream, sorted according to the specified comparator.
     *
     * # Examples
     * ````
     * struct Profile(string name, int balance)
     * 
     * let profiles = [
     *     new Profile("John Doe", 300),
     *     new Profile("Jane Doe", 400),
     *     new Profile("John Smith", 100),
     *     new Profile("Jane Smith", 200)
     * ]
     * 
     * let richest = profiles
     *     .stream()
     *     .sort(|a, b| a.balance - b.balance)
     *     .findLast()
     *     .get()
     *
     * assert richest.name == "Jane Doe"
     * ```
     *
     * The comparator function is invoked to compare left-right values to each other.
     *
     * @param comparator a function that compares two values to each other
     * @return a new stream with ordered elements
     */
    Stream<T> sort(int |T, T| comparator)

    /**
     * Retrieve a stream consisting the elements of this stream, sorted according to the specified key.
     *
     * The key is returned by the extractor function, that is applied for every element.
     * 
     * # Examples
     * ````
     * struct Profile(string name, int balance)
     * 
     * let profiles = [
     *     new Profile("John Doe", 300),
     *     new Profile("Jane Doe", 400),
     *     new Profile("John Smith", 100),
     *     new Profile("Jane Smith", 200)
     * ]
     * 
     * let richest = profiles
     *     .stream()
     *     .sort(|profile| profile.balance)
     *     .findLast()
     *     .get()
     *
     * assert richest.name == "Jane Doe"
     * ```
     *
     * The comparator function is invoked to compare left-right values to each other.
     *
     * @param comparator a function that compares two values to each other
     * @return a new stream with ordered elements
     */
    Stream<T> sort<U>(U |T| extractor)

    /**
     * Retrieve a stream consisting the elements of this stream in a reversed order.
     * 
     * # Examples
     * ```
     * let numbers = [1, 2, 3]
     * let numbers = numbers.stream().reverse().collect()
     * 
     * assert numbers = [3, 2, 1]
     * ```
     * 
     * @return a new stream with a reversed order
     */
    Stream<T> reverse()

    /**
     * Retrieve a new stream consisting the elements of this stream, additionally performing the provided action
     * on each element as elements are consumed from the resulting stream.
     *
     * 
     * # Examples
     * ```
     * let test = ["1", "hello", "2", "four", "3"]
     * 
     * let numbers = test
     *     .stream()
     *     .peek(|e| println($"Raw input: {e}")) 
     *     .filterMap(int::parse)
     *     .peek(|e| println($"Valid number: {e}"))
     *     .collect()
     * 
     * assert numbers == [1, 2, 3]
     * ```
     * 
     * @param action a function to be called on each element when consuming them
     * @return a new stream with with the same exact elements of this stream 
     */
    Stream<T> peek(|T| action)

    /**
     * Collect the elements of this stream to a list.
     * 
     * # Examples
     * ```
     * let test = [0, 1, 2, 3]
     * 
     * let numbers = test
     *     .stream()
     *     .filter(|x| x > 0)
     *     .map(|x| x * 2)
     *     .collect()
     * 
     * assert numbers == [2, 4, 6]
     * ```
     * 
     * @return a list consisting the elements of this stream
     */
    List<T> collect()
}
