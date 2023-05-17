package "util"

/**
 * Represents a container, which includes a value or an error 
 * if the value was unable to be retrieved.
 * 
 * # Examples
 * ```
 * let user = database.fetchUser("John Doe")
 *     .expect("Unable to fetch user.")
 * ```
 * 
 * @since 1.0
 */
public:
class Result<T, E> {
    /**
     * The value of the result.
     */
    private T value

    /**
     * The error if the value was unable to be retrieved.
     */
    private E error

    /**
     * Determine if a value is present in the container.
     * @return true if the result has a value
     */
    bool good() {
        return value != null
    }

    /**
     * Determine if an error is present in the container.
     * @return true if the result has an error
     */
    bool fail() {
        return error != null
    }

    /**
     * Retrieve an optional with the value of the result, that is empty if the result has an error.
     * @return an optional of the result's value
     */
    Option<T> ok() {
        return good() ? Option.of(value) : Option.none()
    }

    /**
     * Retrieve an optional with the error of the result, that is empty, if the result has a value.
     * @return an optional of the result's error
     */
    Option<E> err() {
        return fail() ? Option.of(error) : Option.none()
    }

    /**
     * Retrieve the contained value of the result.
     * If no value is associated for the result, an error is thrown.
     * @return result value
     */
    T unwrap() {
        if (fail())
            panic("Called Result.unwrap() on a failed value.")
        return value
    }

    /**
     * Retrieve the contained value of the result.
     * If no value is associated for the result, the default value is retrieved.
     * @return result value
     */
    T unwrapOr(T def) {
        return fail() ? def : value
    }

    /**
     * Retrieve the contained value of the result.
     * If no value is associated for the result, the default function is called.
     * @return result value
     */
    T unwrapOr(T || def) {
        return fail() ? def() : value
    }

    /**
     * Retrieve the contained value or throw an exception with the specified message.
     * @param msg exception message to be thrown
     * @return option value
     */
    T expect(string msg) {
        if (fail())
            panic(msg)
        return value
    }

    /**
     * Create a new successful result with the specified value.
     * @return a new successful result with a value
     */
    static ok(T value) {
        return Result { value }
    }

    /**
     * Create a new failed result with the specified error.
     * @reutrn a new failed result with an error 
     */
    static err(E error) {
        return Result { error }
    }
}
