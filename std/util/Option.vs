package "util"

/**
 * Represents a container, which may or may not contain a non-null value.
 * 
 * This allows you to safely retrieve values from methods.
 *
 * # Examples
 * ```
 * let user = database.fetchUser("John Doe")
 *     .except("Unable to get user.")
 * ``` 
 * 
 * @since 1.0
 */
public:
struct Option<T> {
    /**
     * The held value of the optional.
     */
    private final T value

    /**
     * Determine if a value is present in the container.
     */
    bool some() {
        return value != null
    }

    /**
     * Determine if no value is present in the container.
     */
    bool empty() {
        return value == null
    }

    /**
     * Retrieve the contained value of the option.
     * If no value is associated for the option, an error is thrown.
     * @return option value
     */
    T unwrap() {
        if (empty())
            panic("Called Option.unwrap() on a None value.")
        return value
    }

    /**
     * Retrieve the contained value or throw an exception with the specified message.
     * @param message exception message to be thrown
     * @return option value
     */
    T except(string message) {
        if (empty())
            panic(message)
        return value
    }

    /**
     * Create a new option  using the specified value.
     */
    static of(T value) {
        return new Option { value }
    }

    /**
     * Create a new option without a value specified.
     * @return new empty option
     */
    static none() {
        return new Option { value: null }        
    }
}
