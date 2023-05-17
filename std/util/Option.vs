package "util"

/**
 * Represents a container, which may or may not contain a non-null value.
 * 
 * This allows you to safely retrieve values from methods.
 *
 * # Examples
 * ```
 * let element = list.get(0)
 *     .except("No such index")
 * ```
 * 
 * @since 1.0
 */
public:
struct Option<T> {
    /**
     * The held value of the optional.
     */
    private T value

    /**
     * Determine if a value is present in the container.
     * @return true if the optional has a value
     */
    bool some() {
        return value != null
    }

    /**
     * Determine if no value is present in the container.
     * @return true if the optional does not have a value
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
            panic("Called Option.unwrap() on a none value.")
        return value
    }

    /**
     * Retrieve the contained value of the option.
     * If no value is associated for the option, the default value is retrieved.
     * @return option value
     */
    T unwrapOr(T def) {
        return empty() ? def : value 
    }

    /**
     * Retrieve the contained value of the option.
     * If no value is associated for the option, the default function is called.
     * @return option value
     */
    T unwrapOr(T || def) {
        return empty() ? def() : value
    }

    /**
     * Retrieve the contained value or throw an exception with the specified message.
     * @param msg exception message to be thrown
     * @return option value
     */
    T expect(string msg) {
        if (empty())
            panic(msg)
        return value
    }

    /**
     * Create a new option using the specified value.
     * @return a new option with the specified value
     */
    static of(T value) {
        return new Option { value }
    }

    /**
     * Create a new option without a value specified.
     * @return a new empty option
     */
    static none() {
        return new Option { }
    }
}
